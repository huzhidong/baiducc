// ivr_callinfo.cpp: implement IvrCallInfo 

#include "ivr_callinfo.h"

namespace ivr {
Logger IvrCallInfo::_m_logger;
ReleaseCauseT::ReleaseCauseT(int32_t value) : _m_value(value) {
}

ReleaseCauseT::~ReleaseCauseT() {
}

void ReleaseCauseT::set_value(int32_t value) {
    _m_value = value;
}

int32_t ReleaseCauseT::get_value() {
    return _m_value;
}

bool ReleaseCauseT::isValid() {
    return _m_value != UNKNOWN;
}

void IvrCallInfo::initial(ivr_session_id_t sessionId, const string& callid, const string& caller, const string& callee)
{
    _m_sessionid = sessionId;
    _m_caller = caller;
    _m_callee = callee;
    _m_callid = callid;
}

IvrCallInfo::IvrCallInfo() : _m_skill(""), _m_route_list(""), _m_agentnum(""), _m_cust_ans_time(0), _m_agt_ans_time(0)
        , _m_agt_alert_time(0), _m_connected_time(0), _m_callee(""), _m_caller(""), _m_exit_flow_time(0)
        , _m_flowbegin_time(0), _m_hangup_time(0), _m_inboundbegin_time(0), _m_recordFilename("")
        , _m_releaseCause(ReleaseCauseT::UNKNOWN), _m_sessionid(0), _m_trans_time(0), _is_update(true)
{
}

IvrCallInfo::~IvrCallInfo()
{
}

void IvrCallInfo::set_inbound_begin_time(time_t t)
{
    _m_inboundbegin_time = t;
}

time_t IvrCallInfo::get_inbound_begin_time()
{
    return _m_inboundbegin_time;
}

void IvrCallInfo::set_flow_begin_time(time_t t)
{
    _m_flowbegin_time = t;
}

void IvrCallInfo::set_cust_ans_time(time_t t)
{
    _m_cust_ans_time = t;
}

void IvrCallInfo::set_agt_ans_time(time_t t)
{
    _m_agt_ans_time = t;
}

void IvrCallInfo::set_agt_alert_time(time_t t)
{
    _m_agt_alert_time = t;
}

void IvrCallInfo::set_connected_time(time_t t)
{
    _m_connected_time = t;
}

void IvrCallInfo::set_trans_time(time_t t)
{
    _m_trans_time = t;
}

void IvrCallInfo::set_hangup_time(time_t t)
{
    _m_hangup_time = t;
    if (!_is_update && _m_route_list != "") {
        std::ostringstream oss;
        oss << "#";
        oss << t;
        _m_route_list+= oss.str();
    }
}

void IvrCallInfo::set_exit_flow_time(time_t t)
{
    _m_exit_flow_time = t;
}

void IvrCallInfo::set_release_cause(int32_t releaseCause)
{
    _m_releaseCause.set_value(releaseCause);
}

void IvrCallInfo::set_record_filename(const string &recordFilename)
{
    _m_recordFilename = recordFilename;
}

void IvrCallInfo::set_skill(time_t t, const std::string &skill)
{
    std::ostringstream oss;
    if (_m_route_list != "") {
        if (!_is_update) {
            oss << "#";
            oss << t;        
        }
        oss << "|";
    }
    oss << skill;
    oss << "#";
    oss << t;
    _m_route_list+= oss.str();
    _m_skill = skill;
    _is_update = false;
}
void IvrCallInfo::update_skill(time_t t, const std::string& skill) {
    std::ostringstream oss;
    oss << "#";
    oss << t;

    _m_route_list += oss.str();
    _is_update = true;
}

void IvrCallInfo::set_appdata(const std::string& appdata) {
    _m_appdata = appdata;
}

std::string IvrCallInfo::get_skill()
{
    return _m_skill;
}

std::string IvrCallInfo::get_callee()
{
    return _m_callee;
}

void IvrCallInfo::set_agent_num(const string &agentnum)
{
    _m_agentnum = agentnum;
}

void IvrCallInfo::reset()
{
    _m_agentnum.clear();
    _m_cust_ans_time = 0;
    _m_connected_time = 0;
    _m_agt_ans_time = 0;
    _m_agt_alert_time = 0;
    _m_callee.clear();
    _m_caller.clear();
    _m_exit_flow_time = 0;
    _m_flowbegin_time = 0;
    _m_hangup_time = 0;
    _m_inboundbegin_time = 0;
    _m_recordFilename.clear();
    _m_releaseCause = ReleaseCauseT::UNKNOWN;
    _m_sessionid = 0;
    _m_skill.clear();
    _m_trans_time = 0;
}

void IvrCallInfo::write_call_log()
{
    char buffer[20480] = {0};
    snprintf(
            buffer, 
            20480, 
            "%s,%s,%s,%lu,%lu,%lu,%lu,%lu,%lu,%lu,%d,%s,%s,%s", 
            _m_callid.c_str(), 
            _m_caller.c_str(), 
            _m_callee.c_str(), 
            _m_flowbegin_time, 
            _m_agt_ans_time,
            _m_hangup_time, 
            _m_trans_time, 
            _m_agt_alert_time, 
            _m_agt_ans_time, 
            _m_exit_flow_time, 
            _m_releaseCause.get_value(), 
            _m_skill.c_str(), 
            _m_route_list.c_str(), 
            _m_appdata.c_str());
    //std::cout << "buffer " << buffer << std::endl;
    IVR_NOTICE("write callinfo, sessionid(%lu), callid(%s)", _m_sessionid, _m_callid.c_str());
    _m_logger.WriteLog(buffer);
}

};
