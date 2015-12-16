// ivr_data_collection.cpp: implement IvrCallDataCollection

#include <json/json.h>
#include "ivr_data_collection.h"

#define CHECK_CONF(name, type) \
    if (name.is_null()) { \
        IVR_WARN("not found %s", #name);\
        return -1; \
    } else if (name.get_type() != type) { \
        IVR_WARN("type is equal, need(%d), given(%d)", type, name.get_type());\
        return -1; \
    }

#define FIND_CALL(sessionid, p) do {\
    iterCall iter_call = _realtime_call.find(sessionid);\
    if (iter_call == _realtime_call.end()) { \
        IVR_WARN("process event, not found sessionid, sessionid(%lu)", sessionid);\
        return -1; \
    } \
    if (iter_call->second ==  NULL) { \
        IVR_WARN("inbound call struct is null, sessionid(%lu)", sessionid); \
        return -1; \
    } \
    p = iter_call->second; \
} while(0)

#define BGCC_LOCK(locker) \
    locker_t w_lock(&locker);\
    if (!w_lock.is_locked()) { \
        IVR_WARN("w_lock failed!"); \
        return -1; \
    }

namespace ivr {
    time_t _m_inboundbegin_time;
    time_t _m_flowbegin_time;
    time_t _m_answer_time;	
    time_t _m_trans_time;
    time_t _m_exit_flow_time;
    time_t _m_hangup_time;
int32_t IvrInboundCall::set_state(int32_t state)
{
    time_t cur_time = time(NULL);
    switch (state) {
        case BEGIN: {
            _m_ivr_callinfo.set_inbound_begin_time(cur_time);
            break;
        }
        case ACCEPT: {
            _m_ivr_callinfo.set_flow_begin_time(cur_time);
            state = INFLOW;
            break;
        }
        case CUSTOMERANSWER: {
            _m_ivr_callinfo.set_cust_ans_time(cur_time);
            break;
        }
        case AGENTANSWER: {
            _m_ivr_callinfo.set_agt_ans_time(cur_time);
            break;
        }
        case CONNECTED: {
            _m_ivr_callinfo.set_connected_time(cur_time);
            break;
        }
        case AGENTALERTING: {
            _m_ivr_callinfo.set_agt_alert_time(cur_time);
            break;
        }
        case TRANSAGENT: {
            _m_ivr_callinfo.set_trans_time(cur_time);
            state = _m_state;
            break;
        }
        case EXITFLOW:
        case CALLWITHOUTFOLW: {
            _m_ivr_callinfo.set_exit_flow_time(cur_time);
            break;
        }
        case THISPARTYHANGUP: {
            _m_ivr_callinfo.set_hangup_time(cur_time);
            _m_ivr_callinfo.set_release_cause(ReleaseCauseT::THISPARTY);
            //write call log
            break;
        }
        case OTHERPARTYHANGUP: {
            _m_ivr_callinfo.set_hangup_time(cur_time);
            _m_ivr_callinfo.set_release_cause(ReleaseCauseT::OTHERPARTY);
            //write call log
            break;
        }
        default:
            break;
    }
    _m_state = state;
    return 0;
}

int32_t IvrInboundCall::get_state()
{
    return _m_state;
}

void IvrInboundCall::init_new_call(const ivr_session_id_t& sessionId, const string &caller, const string &callee)
{
    _m_ivr_callinfo.initial(sessionId, caller, callee);
}

void IvrInboundCall::set_skill(const std::string& skill)
{
    _m_ivr_callinfo.set_skill(skill);
}

std::string IvrInboundCall::get_skill()
{
    return _m_ivr_callinfo.get_skill();
}

std::string IvrInboundCall::get_called()
{
    return _m_ivr_callinfo.get_callee();
}

void IvrInboundCall::set_agent_num(const string &agentnum)
{
    _m_ivr_callinfo.set_agent_num(agentnum);
}

time_t IvrInboundCall::get_begintime()
{
    return _m_ivr_callinfo.get_inbound_begin_time();
}

IvrCallDataCollection& IvrCallDataCollection::instance()
{
    static IvrCallDataCollection mgr;
    return mgr;
}

int32_t IvrCallDataCollection::initialize(const char* path)
{
    //init plat_call_data
    _plat_call_data.cur_accept_num = 0;
    _plat_call_data.cur_inbound_num = 0;
    _plat_call_data.trans_num = 0;
    _plat_call_data.total_inbound_num = 0;
    _plat_call_data.total_accept_num = 0;
    _plat_call_data.giveuptimes = 0;

    //init ivrnum call info
    std::map<string, inbound_script_t>::iterator iter;
    for (iter = g_inbound_conf.dnis_script_map.begin()
    ; iter != g_inbound_conf.dnis_script_map.end(); ++iter) {
        struct IvrCallData *p = new (std::nothrow) struct IvrCallData;
        if (p ==  NULL) {
            IVR_WARN("new ivr num memory failed, ivrnum(%s)", iter->first.c_str());
            return -1;
        }
        _ivrnum_call_data.insert(std::make_pair(iter->first, p));
    }

    if (g_inbound_conf.has_default) {
        struct IvrCallData *p = new (std::nothrow) struct IvrCallData;
        if (p ==  NULL) {
            IVR_WARN("new ivr num memory failed, ivrnum(%s)", iter->first.c_str());
            return -1;
        }
	 _ivrnum_call_data.insert(std::make_pair("default", p));
    }
    // read cached data form file
    _cached_file = path;
    _cached_date = bgcc::TimeUtil::get_date();
    get_data_from_file();
    IVR_NOTICE("ivr data collection has been initialize");
    return 0;
}

int32_t IvrCallDataCollection::uninitialize()
{
    BGCC_LOCK(_m_locker);
    // uninitialize real call info
    for (iterCall iter = _realtime_call.begin(); iter != _realtime_call.end(); ++iter) {
        if (iter->second != NULL) {
            delete iter->second;
            iter->second = NULL;
        }
        _realtime_call.erase(iter->first);
    }
    // uninitialize plat info
    for (IterSkill iter = _plat_call_data.skill_call_data.begin()
            ; iter != _plat_call_data.skill_call_data.end(); ++iter) {
        if (iter->second != NULL) {
            delete iter->second;
            iter->second = NULL;
        }
        _plat_call_data.skill_call_data.erase(iter->first);
    }
    // uninitialize ivrnum info
    for (IterIvrNum iter = _ivrnum_call_data.begin(); iter != _ivrnum_call_data.end(); ++iter) {
        if (iter->second == NULL) {
            _ivrnum_call_data.erase(iter->first);
            continue;
        }
        for (IterSkill iterskill = iter->second->skill_call_data.begin()
            ; iterskill != iter->second->skill_call_data.end(); ++iterskill) {
            if (iterskill->second != NULL) {
                delete iterskill->second;
                iterskill->second = NULL;
            }
           iter->second->skill_call_data.erase(iterskill->first);
        }
        _ivrnum_call_data.erase(iter->first);
    }
    IVR_NOTICE("ivr data collection has been uninitialize");
    return 0;
}

void IvrCallDataCollection::calldata_to_file_block_func()
{
    IVR_NOTICE("ivr data collection thread has start");
    std::string cur_date;
    const static int32_t sleep_time = 30;
    while (!g_stopped) {
        bgcc::TimeUtil::safe_sleep_s(sleep_time);
        cur_date = bgcc::TimeUtil::get_date();
        if (cur_date != _cached_date) {
            reset();
            clear_invaid_call();
            _cached_date = cur_date;
            IVR_DEBUG("not this day, clear date, cachedate(%s), curdate(%s)", 
                        _cached_date.c_str(), cur_date.c_str());
        }
        put_data_to_file();
    }
}

int32_t IvrCallDataCollection::new_inbound_call(const std::string& caller, const std::string& called
                , const std::string& uuid)
{
    IVR_DEBUG("one new inbound call, caller(%s), called(%s), uuid(%s)"
                , caller.c_str(), called.c_str(), uuid.c_str());
    BGCC_LOCK(_m_locker);
    ++_plat_call_data.cur_inbound_num;
    ++_plat_call_data.total_inbound_num;
    _refuse_call.insert(uuid);

    IterIvrNum iter = _ivrnum_call_data.find(called);
    if (iter == _ivrnum_call_data.end()) {
        iter = _ivrnum_call_data.find("default");
    }
    if (iter == _ivrnum_call_data.end()) {
        IVR_WARN("called is not in ivr num, caller(%s), called(%s)", caller.c_str(), called.c_str());
        return 0;
    }
    if (iter->second == NULL) {
        IVR_WARN("ivr num struct is NULL, caller(%s), called(%s)", caller.c_str(), called.c_str());
        return 0;
    }
    ++iter->second->cur_inbound_num;
    ++iter->second->total_inbound_num;
    IVR_DEBUG("update ivr num info, caller(%s), called(%s), uuid(%s)"
                , caller.c_str(), called.c_str(), uuid.c_str());
    return 0;

}

int32_t IvrCallDataCollection::new_inbound_call(const std::string& caller, const std::string& called
                , const ivr_session_id_t& sessionId, const std::string& uuid)
{
    IVR_DEBUG("one new inbound call, caller(%s), called(%s), sessionid(%lu), uuid(%s)"
                    , caller.c_str(), called.c_str(), sessionId, uuid.c_str());
    struct IvrInboundCall *p = new (std::nothrow) struct IvrInboundCall;
    if (p == NULL) {
        IVR_WARN("new inbound call memory failed, caller(%s), called(%s)", caller.c_str(), called.c_str());
        return -1;
    }
    BGCC_LOCK(_m_locker);
    p->init_new_call(sessionId, caller, called);
    p->set_state(IvrInboundCall::ACCEPT);
    ++_plat_call_data.cur_accept_num;
    ++_plat_call_data.total_accept_num;
    ++_plat_call_data.cur_inbound_num;
    ++_plat_call_data.total_inbound_num;
    _realtime_call.insert(std::make_pair(sessionId, p));
    _first_uuid_map.insert(std::make_pair(uuid, sessionId));
    IterIvrNum iter = _ivrnum_call_data.find(called);
    if (iter == _ivrnum_call_data.end()) {
        iter = _ivrnum_call_data.find("default");
    }
    if (iter == _ivrnum_call_data.end()) {
        IVR_WARN("called is not in ivr num, caller(%s), called(%s)", caller.c_str(), called.c_str());
        return 0;
    }
    if (iter->second == NULL) {
        IVR_WARN("ivr num struct is NULL, caller(%s), called(%s)", caller.c_str(), called.c_str());
        return 0;
    }
    ++iter->second->cur_accept_num;
    ++iter->second->total_accept_num;
    ++iter->second->cur_inbound_num;
    ++iter->second->total_inbound_num;
    IVR_DEBUG("update ivr num info, caller(%s), called(%s), sessionid(%lu), uuid(%s)"
                , caller.c_str(), called.c_str(), sessionId, uuid.c_str());
    return 0;
}

int32_t IvrCallDataCollection::del_inbound_call(const ivr_session_id_t& sessionId)
{
    IVR_DEBUG("del inbound call sessionid(%lu)", sessionId);
    BGCC_LOCK(_m_locker);
    iterCall iter = _realtime_call.find(sessionId);
    if (iter != _realtime_call.end()) {
        if (iter->second != NULL) {
            delete iter->second;
            iter->second = NULL;
        }
        _realtime_call.erase(iter->first);
    }
    else {
        IVR_DEBUG("not found inbound call sessionid(%lu)", sessionId);
    }
    return 0;
}

int32_t IvrCallDataCollection::del_inbound_call(const std::string& uuid)
{
    IVR_DEBUG("del inbound call uuid(%s)", uuid.c_str());
    BGCC_LOCK(_m_locker);
    std::set<std::string>::iterator iter = _refuse_call.find(uuid);
    if (iter != _refuse_call.end()) {
        _refuse_call.erase(iter);
    }
    else {
        IVR_DEBUG("not found inbound call uuid(%s)", uuid.c_str());
    }
    return 0;
}

int32_t IvrCallDataCollection::set_state(const ivr_session_id_t& sessionId
                , const int32_t state, const std::string& skill)
{
    IVR_DEBUG("set state sessionid(%lu), state(%d)", sessionId, state);
    BGCC_LOCK(_m_locker);
    iterCall iter = _realtime_call.find(sessionId);
    if (iter == _realtime_call.end()) {
        IVR_DEBUG("not found inbound call sessionid(%lu)", sessionId);
        return -1;
    }
    std::string called = iter->second->get_called();
    switch (state) {
        case IvrInboundCall::BEGIN:
        case IvrInboundCall::ACCEPT:
        case IvrInboundCall::INFLOW:
        case IvrInboundCall::ROUTEBYAGENTID:
        case IvrInboundCall::ROUTEBYAGENTLIST: {
            iter->second->set_state(state);
            break;
        }
        case IvrInboundCall::ROUTEBYSKILL: {
            iter->second->set_state(state);
            iter->second->set_skill(skill);
            break;    
        }
        case IvrInboundCall::TRANSAGENT: {
            ++_plat_call_data.trans_num;
            IterIvrNum iter_ivrnum = _ivrnum_call_data.find(called);
            if (iter_ivrnum != _ivrnum_call_data.end() && iter_ivrnum->second != NULL) {
                ++iter_ivrnum->second->trans_num;
            }
            iter->second->set_state(state);
            break;
        }
        case IvrInboundCall::EXITFLOW: {
            if (iter->second->get_state() == IvrInboundCall::TRANSAGENT) {
                iter->second->set_state(IvrInboundCall::CALLWITHOUTFOLW);
            }
            else {
                iter->second->set_state(state);
            }
            break;
        }
        default:
            IVR_WARN("unknow state, state(%d)", state);
            break;
    }
    return 0;
}

int32_t IvrCallDataCollection::is_giveup_call(IvrInboundCall *call
                , const uint64_t sessionid, const std::string& called)
{
    if (call == NULL) {
        IVR_WARN("call is null");
        return -1;
    }
    if (call->get_state() == IvrInboundCall::ROUTEBYSKILL) {
        ++_plat_call_data.giveuptimes;
        std::string call_skill = call->get_skill();
        if (call_skill == "") {
            IVR_WARN("skill is empty");
            return -1; 
        }
        IterSkill iter_skill = _plat_call_data.skill_call_data.find(call_skill);
        if (iter_skill == _plat_call_data.skill_call_data.end()) {
            struct SkillCallData *p = new (std::nothrow) struct SkillCallData;
            if (p == NULL){
                IVR_WARN("new skill info memory failed, sessionid(%lu), skill(%s)"
                                , sessionid, call_skill.c_str());
                return -1;                        
            }
            ++p->giveuptimes;
             _plat_call_data.skill_call_data.insert(std::make_pair(call_skill, p));
        }
        else {
            if (iter_skill->second == NULL) {
                IVR_WARN("skill struct is null, sessionid(%lu), skill(%s)"
                                , sessionid, call_skill.c_str());
                return -1; 
            }
            ++iter_skill->second->giveuptimes;
        }
        IterIvrNum iter_ivrnum = _ivrnum_call_data.find(called);
        if (iter_ivrnum != _ivrnum_call_data.end() && iter_ivrnum->second != NULL) {
            ++iter_ivrnum->second->giveuptimes;
            iter_skill = iter_ivrnum->second->skill_call_data.find(call_skill);
            if (iter_skill == iter_ivrnum->second->skill_call_data.end()) {
                struct SkillCallData *p = new (std::nothrow) struct SkillCallData;
                if (p == NULL){
                    IVR_WARN("new skill info memory failed, sessionid(%lu), skill(%s)"
                    , sessionid, call_skill.c_str());
                    return -1;                        
                }
                ++p->giveuptimes;
                iter_ivrnum->second->skill_call_data.insert(std::make_pair(call_skill, p));
            }
            else {
                 if (iter_skill->second == NULL) {
                     IVR_WARN("skill struct is null, sessionid(%lu), skill(%s)"
                      , sessionid, call_skill.c_str());
                     return -1; 
                 }
                 ++iter_skill->second->giveuptimes;
            }
        }
    }
    return 0;
}

int32_t IvrCallDataCollection::process_event(ivr_base_event_t* event)
{
    ivr_session_id_t ivrsid = event->sessionId;
    if (event->evt_type != ivr_base_event_t::IMS_EVENT) {
        return -1;
    }
    struct IvrInboundCall *cur_call = NULL;
    BGCC_LOCK(_m_locker);
    FIND_CALL(ivrsid, cur_call);
     cur_call->set_state(IvrInboundCall::INFLOW);    
    return 0;    
}

int32_t IvrCallDataCollection::process_event(struct fs_event& event)
{
    std::string uuid = event.event_data.normal.uuid;
    uint64_t sessionid = event.sessionid;
    IVR_DEBUG("process event, name(%s), caller(%s), called(%s), sessionid(%lu), callid(%s)"
            , event.name
            , event.event_data.normal.caller_no
            , event.event_data.normal.called_no
            , sessionid, uuid.c_str());
    struct IvrInboundCall *cur_call = NULL;
    if (strcasecmp(event.name, "CHANNEL_ANSWER") == 0) {
        std::map<std::string, ivr_session_id_t>::iterator iter;
        if ((iter = _second_uuid_map.find(uuid)) != _second_uuid_map.end()) {
            // agent answer
            sessionid = iter->second;
            BGCC_LOCK(_m_locker);
            FIND_CALL(sessionid, cur_call);
            cur_call->set_state(IvrInboundCall::CUSTOMERANSWER);
            IVR_DEBUG("set call to state(%d), sessionid(%lu)", IvrInboundCall::CUSTOMERANSWER, sessionid);
        }
        else if ((iter = _first_uuid_map.find(uuid)) != _first_uuid_map.end()) {
            // customer answer
            sessionid = iter->second;
            BGCC_LOCK(_m_locker);
            FIND_CALL(sessionid, cur_call);
            cur_call->set_state(IvrInboundCall::AGENTANSWER);
            IVR_DEBUG("set call to state(%d), sessionid(%lu)", IvrInboundCall::AGENTANSWER, sessionid);
        }
    }
    else if (0 == strcasecmp(event.name, "CHANNEL_PROGRESS_MEDIA") ||
                0 == strcasecmp(event.name, "CHANNEL_PROGRESS")) {
        // agent alerting
        std::map<std::string, ivr_session_id_t>::iterator iter;
        if ((iter = _second_uuid_map.find(uuid)) != _second_uuid_map.end()) {
            sessionid = iter->second;
            BGCC_LOCK(_m_locker);
            FIND_CALL(sessionid, cur_call);
            cur_call->set_state(IvrInboundCall::AGENTALERTING);
            IVR_DEBUG("set call to state(%d), sessionid(%lu)", IvrInboundCall::AGENTALERTING, sessionid);
        }
    }
    else if (0 == strcasecmp(event.name, "CHANNEL_ORIGINATE")) {
        BGCC_LOCK(_m_locker);
        FIND_CALL(sessionid, cur_call);
        _second_uuid_map[uuid] = sessionid;
        cur_call->set_agent_num(event.event_data.normal.called_no);
        IVR_DEBUG("add second leg, sessionid(%lu)", sessionid);
    }
    else if (0 == strcasecmp(event.name, "CHANNEL_BRIDGE")) {
        std::map<std::string, ivr_session_id_t>::iterator iter = _second_uuid_map.find(uuid);
        if (iter == _second_uuid_map.end()) {
            IVR_WARN("not found session");
        }
        sessionid = iter->second;
        BGCC_LOCK(_m_locker);
        FIND_CALL(sessionid, cur_call);
        cur_call->set_state(IvrInboundCall::CONNECTED);
        IVR_DEBUG("set call to state(%d), sessionid(%lu)", IvrInboundCall::CONNECTED, sessionid);
    }
    else if (0 == strcasecmp(event.name, "CHANNEL_HANGUP")) {
        std::string other_uuid = event.event_data.normal.other_uuid;
        std::string caller = event.event_data.normal.caller_no;
        std::string called = event.event_data.normal.called_no;
        std::string other_called = event.event_data.normal.other_called_no;
        BGCC_LOCK(_m_locker);
        // first refuse call
        if (_refuse_call.find(uuid) != _refuse_call.end()) {
            _refuse_call.erase(uuid);
            --_plat_call_data.cur_inbound_num;
            IterIvrNum iter_ivrnum = _ivrnum_call_data.find(called);
            if (iter_ivrnum != _ivrnum_call_data.end() && iter_ivrnum->second != NULL) {
                --iter_ivrnum->second->cur_inbound_num;
            }
            IVR_NOTICE("one refuse call hangup,caller(%s), called(%s)", caller.c_str(), called.c_str());
        }
        // accept call
        std::map<std::string, ivr_session_id_t>::iterator iter;
        if ((iter = _first_uuid_map.find(uuid)) != _first_uuid_map.end()) {
            // customer hangup
            sessionid = iter->second;
            FIND_CALL(sessionid, cur_call);
            is_giveup_call(cur_call, sessionid, called);
            cur_call->set_state(IvrInboundCall::THISPARTYHANGUP);
            --_plat_call_data.cur_accept_num;
            --_plat_call_data.cur_inbound_num;
            IterIvrNum iter_ivrnum = _ivrnum_call_data.find(called);
            if (iter_ivrnum != _ivrnum_call_data.end() && iter_ivrnum->second != NULL) {
                --iter_ivrnum->second->cur_accept_num;
                --iter_ivrnum->second->cur_inbound_num;
            }
            if (cur_call != NULL) {
                delete cur_call;
                cur_call = NULL;
            }
            _realtime_call.erase(sessionid);
            _first_uuid_map.erase(uuid);
            _second_uuid_map.erase(other_uuid);
            IVR_DEBUG("set call to state(%d), sessionid(%lu)", IvrInboundCall::THISPARTYHANGUP, sessionid);
        }
        else if ((iter = _second_uuid_map.find(uuid)) != _second_uuid_map.end()) {
            // agent hangup
            sessionid = iter->second;
            FIND_CALL(sessionid, cur_call);
            cur_call->set_state(IvrInboundCall::OTHERPARTYHANGUP);
            --_plat_call_data.cur_accept_num;
            --_plat_call_data.cur_inbound_num;
            IterIvrNum iter_ivrnum = _ivrnum_call_data.find(other_called);
            if (iter_ivrnum != _ivrnum_call_data.end() && iter_ivrnum->second != NULL) {
                --iter_ivrnum->second->cur_accept_num;
                --iter_ivrnum->second->cur_inbound_num;
            }
            if (cur_call != NULL) {
                delete cur_call;
                cur_call = NULL;
            }
            _realtime_call.erase(sessionid);
            _second_uuid_map.erase(uuid);
            _first_uuid_map.erase(other_uuid);
            IVR_DEBUG("set call to state(%d), sessionid(%lu)", IvrInboundCall::OTHERPARTYHANGUP, sessionid);
        }
        //clear data        
    }
    IVR_DEBUG("process event end, name(%s), caller(%s), called(%s), sessionid(%lu), callid(%s), curcalnum(%d)"
            , event.name
            , event.event_data.normal.caller_no
            , event.event_data.normal.called_no
            , sessionid, uuid.c_str(), (int32_t)_realtime_call.size());
    return 0;
}

int32_t IvrCallDataCollection::get_call_data(struct IvrCallData* p, std::string& result)
{
    std::string fail_str = "{\"result\":\"-1\",\"data\":\"memory error\"}";
    if (p == NULL) {
        IVR_WARN("calldata is NULL");
        result = fail_str;
        return -1;
    }
    json_object *root = json_object_new_object();
    if (root == NULL) {
        IVR_WARN("new root json object failed");
        result = fail_str;
        return -1;
    }
    json_object *calldata = json_object_new_object();
    if (calldata == NULL) {
        IVR_WARN("new calldata json object failed");
        result = fail_str;
        json_object_put(root);
        return -1;
    }
    json_object *platdata = json_object_new_object();
    if (calldata == NULL) {
        IVR_WARN("new platdata json object failed");
        result = fail_str;
        json_object_put(root);
        json_object_put(calldata);
        return -1;
    }
    json_object *skilldata = json_object_new_array();
    if (skilldata == NULL) {
        IVR_WARN("new skilldata json object failed");
        result = fail_str;
        json_object_put(root);
        json_object_put(calldata);
        json_object_put(platdata);
        return -1;
    }
    json_object_object_add(platdata, "CurInboundNum", json_object_new_int(p->cur_inbound_num));
    json_object_object_add(platdata, "CurAcceptNum", json_object_new_int(p->cur_accept_num));
    json_object_object_add(platdata, "TotalInboundNum", json_object_new_int(p->total_inbound_num));
    json_object_object_add(platdata, "TotalAcceptNum", json_object_new_int(p->total_accept_num));
    json_object_object_add(platdata, "GiveupNum", json_object_new_int(p->giveuptimes));
    json_object_object_add(platdata, "TransNum", json_object_new_int(p->trans_num));
    for (IterSkill iter = p->skill_call_data.begin()
            ; iter != p->skill_call_data.end(); ++iter) {
        if (iter->second != NULL) {
            json_object *skillinfo = json_object_new_object();
            if (skillinfo == NULL) {
                IVR_WARN("new skilinfo json object failed, skill(%s)", iter->first.c_str());
                continue;
            }
            json_object_object_add(skillinfo, "skillname", json_object_new_string(iter->first.c_str()));
            json_object_object_add(skillinfo, "GiveupNum", json_object_new_int(iter->second->giveuptimes));
            json_object_array_add(skilldata, skillinfo);
        }
    }
    json_object_object_add(calldata, "platinfo", platdata);
    json_object_object_add(calldata, "skillinfo", skilldata);
    json_object_object_add(root, "result", json_object_new_string("0"));
    json_object_object_add(root, "data", calldata);
    result = json_object_to_json_string(root);
    IVR_DEBUG("get call data by plat success, data(%s)", result.c_str());
    //IVR_DEBUG("get call data by plat success");
    json_object_put(root);
    return 0;
}

int32_t IvrCallDataCollection::get_inbound_by_plat(std::string& result)
{
    IVR_DEBUG("get inbound info by plat");
    std::string fail_str = "{\"result\":\"-1\",\"data\":\"lock failed\"}";
    BGCC_LOCK(_m_locker);
    return get_call_data(&_plat_call_data, result);
}

int32_t IvrCallDataCollection::get_inbound_by_ivrnum(const std::string& ivrnum, std::string& result)
{
    IVR_DEBUG("get inbound info by ivrnum, ivrnum(%s)", ivrnum.c_str());
    std::string fail_str = "{\"result\":\"-1\",\"data\":\"lock failed\"}";
    BGCC_LOCK(_m_locker);
    fail_str = "{\"result\":\"-1\",\"data\":\"not find ivrnum\"}";
    IterIvrNum iter = _ivrnum_call_data.find(ivrnum);
    if (iter == _ivrnum_call_data.end()) {
        IVR_WARN("not find ivr num, ivrnum(%s)", ivrnum.c_str());
        result = fail_str;
        return -1;
    }
    return get_call_data(iter->second, result);
}

int32_t IvrCallDataCollection::get_inbound_call_data(const int32_t type
                       , const std::string& input, std::string& result)
{
    if (type == GETBYPLAT) {
        return get_inbound_by_plat(result);
    }
    else if (type == GETBYIVRNUM) {
        return get_inbound_by_ivrnum(input, result);
    }
    return -1;
}

int32_t IvrCallDataCollection::get_data_from_file()
{
    reset();
    std::string filename = _cached_file;
    bgcc2::ConfUnit root;
    if(!bgcc2::ConfLoader::load_conf(filename.c_str(), root)) {
        IVR_WARN("open cached file failed ,path(%s)", filename.c_str());
        return -1;
    }
    IVR_NOTICE("begin load =========================================");
    // load date
    bgcc2::ConfUnit& section = root["Date"];
    if(section.is_null()) {
        IVR_WARN("not find date section");
        return -1;
    }
    bgcc2::ConfUnit& date = section["date"];
    CHECK_CONF(date, bgcc::ConfUnit::UT_STRING);
    string cacheddate = date.to_string();
    IVR_NOTICE("|Cached Date  | %s", cacheddate.c_str());

    // check is today?
    std::string curdate = bgcc::TimeUtil::get_date();
    if (curdate != cacheddate) {
        IVR_WARN("data is not this day, cacheddate(%s), curdate(%s)", cacheddate.c_str(), curdate.c_str());
        return -1;
    }

    //load plat info
    bgcc2::ConfUnit& section_plat = root["PlatInfo"];
    if(section.is_null()) {
        IVR_WARN("not find platinfo section");
        return -1;
    }
    bgcc2::ConfUnit& total_inbound_num = section_plat["TotalInboundNum"];
    bgcc2::ConfUnit& trans_num = section_plat["TransNum"];
    bgcc2::ConfUnit& total_accept_num = section_plat["TotalAcceptNum"];
    bgcc2::ConfUnit& giveuptimes = section_plat["GiveupTimes"];
    bgcc2::ConfUnit& skill_info = section_plat["SkillInfo"];
    CHECK_CONF(total_inbound_num, bgcc::ConfUnit::UT_STRING);
    CHECK_CONF(trans_num, bgcc::ConfUnit::UT_STRING);
    CHECK_CONF(total_accept_num, bgcc::ConfUnit::UT_STRING);
    CHECK_CONF(giveuptimes, bgcc::ConfUnit::UT_STRING);
    CHECK_CONF(skill_info, bgcc::ConfUnit::UT_STRING);
    if (!bgcc::StringUtil::str2uint32(total_inbound_num.to_string().c_str(), _plat_call_data.total_inbound_num)) {
        IVR_WARN("parse total_inbound_num(%s) failed", total_inbound_num.to_string().c_str());
        return -1;
    }
    if (!bgcc::StringUtil::str2uint32(trans_num.to_string().c_str(), _plat_call_data.trans_num)) {
        IVR_WARN("parse trans_num(%s) failed", trans_num.to_string().c_str());
        return -1;
    }
    if (!bgcc::StringUtil::str2uint32(total_accept_num.to_string().c_str(), _plat_call_data.total_accept_num)) {
        IVR_WARN("parse total_accept_num(%s) failed", total_accept_num.to_string().c_str());
        return -1;
    }
    if (!bgcc::StringUtil::str2uint32(giveuptimes.to_string().c_str(), _plat_call_data.giveuptimes)) {
        IVR_WARN("parse giveuptimes(%s) failed", giveuptimes.to_string().c_str());
        return -1;
    }

    IVR_NOTICE("|TotalInboundNum  | %d", _plat_call_data.total_inbound_num);
    IVR_NOTICE("|TransNum  | %d", _plat_call_data.trans_num);
    IVR_NOTICE("|TotalAcceptNum  | %d", _plat_call_data.total_accept_num);
    IVR_NOTICE("|GiveupTimes  | %d", _plat_call_data.giveuptimes);

    std::vector<std::string> vecp;
    bgcc::StringUtil::split_string(skill_info.to_string(), ",", vecp, true);
    for (std::vector<std::string>::iterator iter = vecp.begin(); iter != vecp.end(); ++iter) {
        size_t pos_equal = iter->find(':');
        if (pos_equal == std::string::npos){
            IVR_WARN("not find : string(%s)", iter->c_str());
            continue;
        }
        std::string key = iter->substr(0, pos_equal);
        std::string var = iter->substr(pos_equal + 1);
        struct SkillCallData *p = new(std::nothrow) struct SkillCallData;
        if (p == NULL) {
            IVR_WARN("new skill info failed, skill(%s)", key.c_str());
            return -1;
        }
        bgcc::StringUtil::str2uint32(var.c_str(), p->giveuptimes);
        _plat_call_data.skill_call_data.insert(std::make_pair(key, p));
        IVR_NOTICE("|SkillName(%s)  | GiveupTimes(%d)", key.c_str(), p->giveuptimes);
    }

    //load ivr num info
    bgcc2::ConfUnit& section_ivrnum = root["IvrNumInfo"];
    if(section.is_null()) {
        IVR_WARN("not find platinfo section");
        return -1;
    }
    for(bgcc2::ConfUnit::const_iterator iter = section_ivrnum.begin()
            ; iter != section_ivrnum.end(); ++iter) {
        struct IvrCallData *info = new (std::nothrow) struct IvrCallData;
        if (info == NULL) {
            IVR_WARN("new ivrnum info failed");
            return -1;
        }
        bgcc2::ConfUnit& ivrnum = **iter;
        bgcc2::ConfUnit& name = ivrnum["IvrNum"];
        bgcc2::ConfUnit& total_inbound_num_ivrnum = ivrnum["TotalInboundNum"];
        bgcc2::ConfUnit& trans_num_ivrnum = ivrnum["TransNum"];
        bgcc2::ConfUnit& total_accept_num_ivrnum = ivrnum["TotalAcceptNum"];
        bgcc2::ConfUnit& giveuptimes_ivrnum = ivrnum["GiveupTimes"];
        bgcc2::ConfUnit& skill_info_ivrnum = ivrnum["SkillInfo"];
        CHECK_CONF(name, bgcc::ConfUnit::UT_STRING);
        CHECK_CONF(total_inbound_num_ivrnum, bgcc::ConfUnit::UT_STRING);
        CHECK_CONF(trans_num_ivrnum, bgcc::ConfUnit::UT_STRING);
        CHECK_CONF(total_accept_num_ivrnum, bgcc::ConfUnit::UT_STRING);
        CHECK_CONF(giveuptimes_ivrnum, bgcc::ConfUnit::UT_STRING);
        CHECK_CONF(skill_info_ivrnum, bgcc::ConfUnit::UT_STRING);
        if (!bgcc::StringUtil::str2uint32(total_inbound_num_ivrnum.to_string().c_str(), info->total_inbound_num)) {
            IVR_WARN("parse total_inbound_num(%s) failed", total_inbound_num_ivrnum.to_string().c_str());
            return -1;
        }
        if (!bgcc::StringUtil::str2uint32(trans_num_ivrnum.to_string().c_str(), info->trans_num)) {
            IVR_WARN("parse trans_num(%s) failed", trans_num_ivrnum.to_string().c_str());
            return -1;
        }
        if (!bgcc::StringUtil::str2uint32(total_accept_num_ivrnum.to_string().c_str(), info->total_accept_num)) {
            IVR_WARN("parse total_accept_num(%s) failed", total_accept_num_ivrnum.to_string().c_str());
            return -1;
        }
        if (!bgcc::StringUtil::str2uint32(giveuptimes_ivrnum.to_string().c_str(), info->giveuptimes)) {
            IVR_WARN("parse giveuptimes(%s) failed", giveuptimes_ivrnum.to_string().c_str());
            return -1;
        }
        IVR_NOTICE("|IvrNum  | %s", name.to_string().c_str());
        IVR_NOTICE("    |TotalInboundNum  | %d", info->total_inbound_num);
        IVR_NOTICE("    |TransNum  | %d", info->trans_num);
        IVR_NOTICE("    |TotalAcceptNum  | %d", info->total_accept_num);
        IVR_NOTICE("    |GiveupTimes  | %d", info->giveuptimes);
        std::vector<std::string> vecp;
        bgcc::StringUtil::split_string(skill_info_ivrnum.to_string(), ",", vecp, true);
        for (std::vector<std::string>::iterator iter_v = vecp.begin(); iter_v != vecp.end(); ++iter_v) {
            size_t pos_equal = iter_v->find(':');
            if (pos_equal == std::string::npos){
                IVR_WARN("not find : string(%s)", iter_v->c_str());
                continue;
            }
            std::string key = iter_v->substr(0, pos_equal);
            std::string var = iter_v->substr(pos_equal + 1);
            struct SkillCallData *p = new(std::nothrow) struct SkillCallData;
            if (p == NULL) {
                IVR_WARN("new ivrnum skill info failed, ivrnum(%s), skill(%s)"
                    , name.to_string().c_str(), key.c_str());
                return -1;
            }
            bgcc::StringUtil::str2uint32(var.c_str(), p->giveuptimes);
            info->skill_call_data.insert(std::make_pair(key, p));
            IVR_NOTICE("    |SkillName(%s)  | GiveupTimes(%d)", key.c_str(), p->giveuptimes);
        }
        _ivrnum_call_data.insert(std::make_pair(name.to_string(), info));
    }

    IVR_NOTICE("begin end =========================================");   
    return 0;
}

int32_t IvrCallDataCollection::put_data_to_file()
{
    std::ofstream out(_cached_file.c_str(), std::ios::out);
    if (!out.is_open()){
        IVR_WARN("open cached file failed ,path(%s)", _cached_file.c_str());
        return -1;
    }
    // put date
    string curdate = bgcc::TimeUtil::get_date();
    out << "[Date]" << "\n";
    out << "date = " << curdate << "\n";

    //put plat info
    out << "[PlatInfo]" << "\n"; 
    out << "TotalInboundNum = " << _plat_call_data.total_inbound_num << "\n";
    out << "TransNum = " << _plat_call_data.trans_num << "\n";
    out << "TotalAcceptNum = " << _plat_call_data.total_accept_num << "\n";
    out << "GiveupTimes = " << _plat_call_data.giveuptimes << "\n";
    out << "SkillInfo = "; 
    for (IterSkill iter = _plat_call_data.skill_call_data.begin()
            ; iter != _plat_call_data.skill_call_data.end(); ++iter) {
        if (iter->second != NULL) {
            if (iter == _plat_call_data.skill_call_data.begin()) {
                out << iter->first << ":" << iter->second->giveuptimes;
            }
            else {
                out << "," << iter->first << ":" << iter->second->giveuptimes;
            }
        }
    }
    out << "\n";

    // put ivrnum info
    for (IterIvrNum iter_ivrnum = _ivrnum_call_data.begin()
            ; iter_ivrnum != _ivrnum_call_data.end(); ++iter_ivrnum) {
        if (iter_ivrnum->second == NULL) {
            IVR_WARN("calldata is NULL while put ivrnum info to file, ivrnum(%s)", iter_ivrnum->first.c_str());
            continue;
        }
        out << "[@IvrNumInfo]" << "\n"; 
        out << "IvrNum = " << iter_ivrnum->first << "\n";
        out << "TotalInboundNum = " << iter_ivrnum->second->total_inbound_num << "\n";
        out << "TransNum = " << iter_ivrnum->second->trans_num << "\n";
        out << "TotalAcceptNum = " << iter_ivrnum->second->total_accept_num << "\n";
        out << "GiveupTimes = " << iter_ivrnum->second->giveuptimes << "\n";
        out << "SkillInfo = "; 
        for (IterSkill iter = iter_ivrnum->second->skill_call_data.begin()
                ; iter != iter_ivrnum->second->skill_call_data.end(); ++iter) {
            if (iter->second != NULL) {
                if (iter == iter_ivrnum->second->skill_call_data.begin()) {
                    out << iter->first << ":" << iter->second->giveuptimes;
                }
                else {
                    out << "," << iter->first << ":" << iter->second->giveuptimes;
                }
            }
        }
        out << "\n";
    }
    return 0;
}

void IvrCallDataCollection::clear_invaid_call()
{
    IVR_NOTICE("clear invaid call");
    locker_t w_lock(&_m_locker);    
    if (!w_lock.is_locked()) {
        IVR_WARN("w_lock failed!");
        return;
    }
    const static time_t interval = 6 * 60 * 30;
    time_t cur_time = time(NULL);
    for (iterCall iter = _realtime_call.begin(); iter != _realtime_call.end(); ++iter) {
        if (iter->second == NULL) {
            IVR_NOTICE("clear one invaid call, sessionid(%lu)", iter->first);
            _realtime_call.erase(iter->first);
            continue;
        }
        if (cur_time - iter->second->get_begintime() > interval) {
            IVR_NOTICE("clear one invaid call, sessionid(%lu)", iter->first);
            // clear first uuid_sessiond
            std::map<std::string, ivr_session_id_t>::iterator iter_uuid;
            for (iter_uuid = _first_uuid_map.begin(); iter_uuid != _first_uuid_map.end(); ++iter_uuid) {
                if (iter_uuid->second == iter->first) {
                    _first_uuid_map.erase(iter_uuid->first);
                }
            }
            // clear second uuid_sessionid
            for (iter_uuid = _second_uuid_map.begin(); iter_uuid != _second_uuid_map.end(); ++iter_uuid) {
                if (iter_uuid->second == iter->first) {
                    _second_uuid_map.erase(iter_uuid->first);
                }
            }
            delete iter->second;
            iter->second = NULL;
            _realtime_call.erase(iter->first);
        }        
    }
}

void IvrCallDataCollection::reset()
{
    locker_t w_lock(&_m_locker);    
    if (!w_lock.is_locked()) {
        IVR_WARN("w_lock failed!");
        return;
    }
    // clear plat data
    _plat_call_data.trans_num = 0;
    _plat_call_data.total_inbound_num = 0;
    _plat_call_data.total_accept_num = 0;
    _plat_call_data.giveuptimes = 0;
    IVR_NOTICE("clear plat info");
    for (IterSkill iter = _plat_call_data.skill_call_data.begin()
        ; iter !=  _plat_call_data.skill_call_data.end()
        ; ++iter) {
        if (iter->second != NULL) {
            delete iter->second;
            iter->second = NULL;
        }
        _plat_call_data.skill_call_data.erase(iter->first);
        IVR_NOTICE("clear skill info, skill(%s)", iter->first.c_str());
    }

    // clear ivrnum data
    for (IterIvrNum iter = _ivrnum_call_data.begin(); iter != _ivrnum_call_data.end(); ++iter) {
        if (iter->second == NULL) {
            IVR_WARN("ivrnum info is NULL, ivrnum(%s)", iter->first.c_str());
            if (g_inbound_conf.dnis_script_map.find(iter->first) 
                    != g_inbound_conf.dnis_script_map.end()) {
                struct IvrCallData *p = new (std::nothrow) struct IvrCallData;
                if (p == NULL) {
                    IVR_WARN("new ivrnum struct failed, ivrnum(%s)", iter->first.c_str());
                    _ivrnum_call_data.erase(iter->first);
                   continue;
                }
                _ivrnum_call_data[iter->first] = p;
            }
            else {
                _ivrnum_call_data.erase(iter->first);
            }
           continue;
        }
        iter->second->trans_num = 0;
        iter->second->total_inbound_num = 0;
        iter->second->total_accept_num = 0;
        iter->second->giveuptimes = 0;
        IVR_NOTICE("clear ivrnum plat info, ivrnum(%s)", iter->first.c_str()); 
        for (IterSkill iterskill = iter->second->skill_call_data.begin()
        ; iterskill !=  iter->second->skill_call_data.end()
        ; ++iterskill) {
        if (iterskill->second != NULL) {
            delete iterskill->second;
            iterskill->second = NULL;
        }
        iter->second->skill_call_data.erase(iterskill->first);
        IVR_NOTICE("clear ivrnum skill info, ivrnum(%s), skill(%s)", 
                    iter->first.c_str(), iterskill->first.c_str());
        }
    }
}

};
