// acd_data_collection.cpp: implement AcdDataCollection

#include <json/json.h>
#include "acd_data_collection.h"
#include "acd_tool.h"

#define CHECK_CONF(name, type) \
    if (name.is_null()) { \
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,\
            "not found %s", #name);\
        return -1; \
    } else if (name.get_type() != type) { \
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,\
            "type is equal, need(%d), given(%d)", type, name.get_type());\
        return -1; \
    }

namespace acd {
void AcdCallDataCollection::initialize(const char* path)
{
    reset();
    if (path ==  NULL) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
            "data cached path is NULL");
        return;
    }
    _cached_file = path;
    _cached_date = bgcc::TimeUtil::get_date();
    _cached_second = bgcc::TimeUtil::get_timestamp_s();
    get_data_from_file();
    acd_tool::m_logger.WriteLog(LOG_LEVEL_NOTICE, __FILE__, __LINE__, __FUNCTION__,
        "data collection has initialize");
}

void AcdCallDataCollection::unInitialize()
{
    reset();
}

int32_t AcdCallDataCollection::get_data_from_file()
{
    string filename = _cached_file;
    bgcc2::ConfUnit root;
    if(!bgcc2::ConfLoader::load_conf(filename.c_str(), root)) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
            "open cached file failed ,path(%s)", filename.c_str());
        return -1;
    }
    acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
        "begin load =========================================");    

    // load date
    bgcc2::ConfUnit& section = root["Date"];
    if(section.is_null()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
            "not find date section");
        return -1;
    }
    bgcc2::ConfUnit& date = section["date"];
    CHECK_CONF(date, bgcc::ConfUnit::UT_STRING);
    string cacheddate = date.to_string();
    acd_tool::m_logger.WriteLog(LOG_LEVEL_NOTICE, __FILE__, __LINE__, __FUNCTION__,
        "|Cached Date  | %s", cacheddate.c_str());

    // check is today?
    string curdate = bgcc::TimeUtil::get_date();
    if (curdate != cacheddate) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
            "data is not this day, cacheddate(%s), curdate(%s)", cacheddate.c_str(), curdate.c_str());
        return -1;
    }

    // load cc plat info
    bgcc2::ConfUnit& section1 = root["PlatCallData"];
    if(section1.is_null()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
            "not find platcalldata section");
        return -1;
    }

    bgcc2::ConfUnit& out_call_num= section1["OUTCALLNUM"];
    bgcc2::ConfUnit& out_ans_num= section1["OUTANSNUM"];
    bgcc2::ConfUnit& out_call_time= section1["OUTCALLTIME"];
    bgcc2::ConfUnit& in_call_time= section1["INCALLTIME"];
    bgcc2::ConfUnit& in_alert_time= section1["INALERTTIME"];
    bgcc2::ConfUnit& in_ans_num= section1["INANWNUM"];
    bgcc2::ConfUnit& in_call_num= section1["INCALLNUM"];
    CHECK_CONF(out_call_num, bgcc::ConfUnit::UT_STRING);
    CHECK_CONF(out_ans_num, bgcc::ConfUnit::UT_STRING);
    CHECK_CONF(out_call_time, bgcc::ConfUnit::UT_STRING);
    CHECK_CONF(in_call_time, bgcc::ConfUnit::UT_STRING);
    CHECK_CONF(in_alert_time, bgcc::ConfUnit::UT_STRING);
    CHECK_CONF(in_ans_num, bgcc::ConfUnit::UT_STRING);
    CHECK_CONF(in_call_num, bgcc::ConfUnit::UT_STRING);
    if (!bgcc::StringUtil::str2uint32(out_call_num.to_string().c_str(), _cc_call_data.outbound_call_num)) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
            "parse outcallnum(%s) failed", out_call_num.to_string().c_str());
        return -1;
    }
    if (!bgcc::StringUtil::str2uint32(out_ans_num.to_string().c_str(), _cc_call_data.outbound_ans_num)) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
            "parse outansnum(%s) failed", out_ans_num.to_string().c_str());
        return -1;
    }
    if (!bgcc::StringUtil::str2uint32(out_call_time.to_string().c_str(), _cc_call_data.outbound_call_time)) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
            "parse outcalltime(%s) failed", out_call_time.to_string().c_str());
        return -1;
    }
    if (!bgcc::StringUtil::str2uint32(in_call_time.to_string().c_str(), _cc_call_data.inbound_call_time)) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
            "parse incalltime(%s) failed", in_call_time.to_string().c_str());
        return -1;
    }
    if (!bgcc::StringUtil::str2uint32(in_alert_time.to_string().c_str(), _cc_call_data.inbound_alerting_time)) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
            "parse inalerttime(%s) failed", in_alert_time.to_string().c_str());
        return -1;
    }
    if (!bgcc::StringUtil::str2uint32(in_ans_num.to_string().c_str(), _cc_call_data.inbound_ans_num)) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
            "parse inansnum(%s) failed", in_ans_num.to_string().c_str());
        return -1;
    }
    if (!bgcc::StringUtil::str2uint32(in_call_num.to_string().c_str(), _cc_call_data.inbound_call_num)) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
            "parse incallnum(%s) failed", out_call_num.to_string().c_str());
        return -1;
    }
    acd_tool::m_logger.WriteLog(LOG_LEVEL_NOTICE, __FILE__, __LINE__, __FUNCTION__,
        "|OUTCALLNUM  | %d", _cc_call_data.outbound_call_num);
    acd_tool::m_logger.WriteLog(LOG_LEVEL_NOTICE, __FILE__, __LINE__, __FUNCTION__,
        "|OUTANSNUM  | %d", _cc_call_data.outbound_ans_num);
    acd_tool::m_logger.WriteLog(LOG_LEVEL_NOTICE, __FILE__, __LINE__, __FUNCTION__,
        "|OUTCALLTIME  | %d", _cc_call_data.outbound_call_time);
    acd_tool::m_logger.WriteLog(LOG_LEVEL_NOTICE, __FILE__, __LINE__, __FUNCTION__,
        "|INCALLTIME  | %d", _cc_call_data.inbound_call_time);
    acd_tool::m_logger.WriteLog(LOG_LEVEL_NOTICE, __FILE__, __LINE__, __FUNCTION__,
        "|INALERTTIME  | %d", _cc_call_data.inbound_alerting_time);
    acd_tool::m_logger.WriteLog(LOG_LEVEL_NOTICE, __FILE__, __LINE__, __FUNCTION__,
        "|INANSNUM  | %d", _cc_call_data.inbound_ans_num);
    acd_tool::m_logger.WriteLog(LOG_LEVEL_NOTICE, __FILE__, __LINE__, __FUNCTION__,
        "|INCALLNUM  | %d", _cc_call_data.inbound_call_num);

    //begin load skill info
    bgcc2::ConfUnit& section3 = root["SkillCallData"];
    if(section3.is_null()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_NOTICE, __FILE__, __LINE__, __FUNCTION__,
            "not found SkillCallData section");
        return -1;
    }

    for(bgcc2::ConfUnit::const_iterator itr = section3.begin(); itr != section3.end(); ++itr) {
        bgcc2::ConfUnit& skill = **itr;
        bgcc2::ConfUnit& skillname = skill["SkillName"];
        bgcc2::ConfUnit& calltime = skill["InCallTime"];
        bgcc2::ConfUnit& alerttime = skill["InAlertTime"];
        bgcc2::ConfUnit& ansnum = skill["InAnsNum"];
        bgcc2::ConfUnit& callnum = skill["InCallNum"];
        CHECK_CONF(skillname, bgcc::ConfUnit::UT_STRING);
        CHECK_CONF(calltime, bgcc::ConfUnit::UT_STRING);
        CHECK_CONF(alerttime, bgcc::ConfUnit::UT_STRING);
        CHECK_CONF(ansnum, bgcc::ConfUnit::UT_STRING);
        SkillCallData* p = new (std::nothrow) SkillCallData;
	    if (p == NULL) {
            acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                "new skillinfo failed");
            return -1;            
	    }
        if (!bgcc::StringUtil::str2uint32(calltime.to_string().c_str(), p->inbound_call_time)) {
            acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                "parse skill calltime(%s) failed", calltime.to_string().c_str());
            return -1;
        }
        if (!bgcc::StringUtil::str2uint32(alerttime.to_string().c_str(), p->inbound_alerting_time)) {
            acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                "parse skill alerttime(%s) failed", alerttime.to_string().c_str());
            return -1;
        }
        if (!bgcc::StringUtil::str2uint32(callnum.to_string().c_str(), p->inbound_call_num)) {
            acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                "parse skill callnum(%s) failed", callnum.to_string().c_str());
            return -1;
        }
        if (!bgcc::StringUtil::str2uint32(ansnum.to_string().c_str(), p->inbound_answer_num)) {
            acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                "parse skill ansnum(%s) failed", ansnum.to_string().c_str());
            return -1;
        }
        _skill_call_info.insert(std::make_pair(skillname.to_string(), p));
        acd_tool::m_logger.WriteLog(LOG_LEVEL_NOTICE, __FILE__, __LINE__, __FUNCTION__,
            "|SKILLNAME  | %s", skillname.to_string().c_str());
        acd_tool::m_logger.WriteLog(LOG_LEVEL_NOTICE, __FILE__, __LINE__, __FUNCTION__,
            "        |CALLTIME | %d", p->inbound_call_time);
        acd_tool::m_logger.WriteLog(LOG_LEVEL_NOTICE, __FILE__, __LINE__, __FUNCTION__,
            "        |ALERTTIME  | %d", p->inbound_alerting_time);
        acd_tool::m_logger.WriteLog(LOG_LEVEL_NOTICE, __FILE__, __LINE__, __FUNCTION__,
            "        |CALLNUM | %d", p->inbound_call_num);
        acd_tool::m_logger.WriteLog(LOG_LEVEL_NOTICE, __FILE__, __LINE__, __FUNCTION__,
            "        |ANSNUM | %d", p->inbound_answer_num);
    } 
    acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
        "begin end =========================================");   
    return 0;
}

int32_t AcdCallDataCollection::put_data_to_file()
{
    std::ofstream out(_cached_file.c_str(), std::ios::out);
    if (!out.is_open()){
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
            "open cached file failed ,path(%s)", _cached_file.c_str());
        return -1;
    }
    // put date
    string curdate = bgcc::TimeUtil::get_date();
    out << "[Date]" << "\n";
    out << "date = " << curdate << "\n";

    // put plat call data
    out << "[PlatCallData]" << "\n";
    out << "OUTCALLNUM = " << _cc_call_data.outbound_call_num << "\n";
    out << "OUTANSNUM = " << _cc_call_data.outbound_ans_num << "\n";
    out << "OUTCALLTIME = " << _cc_call_data.outbound_call_time << "\n";
    out << "INCALLTIME = " << _cc_call_data.inbound_call_time << "\n";
    out << "INALERTTIME = " << _cc_call_data.inbound_call_time << "\n";
    out << "INANWNUM = " << _cc_call_data.inbound_ans_num << "\n";
    out << "INCALLNUM = " << _cc_call_data.inbound_call_num << "\n";


    // load skill call data
    for (iter iter = _skill_call_info.begin(); iter != _skill_call_info.end(); ++iter) {
        out << "[@SkillCallData]" << "\n";
        out << "SkillName = " << iter->first.c_str() << "\n";
        out << "InCallTime = " << iter->second->inbound_call_time << "\n";
        out << "InAlertTime = " << iter->second->inbound_alerting_time << "\n";
        out << "InCallNum = " << iter->second->inbound_call_num << "\n";
        out << "InAnsNum = " << iter->second->inbound_answer_num << "\n";
    }
    out.close();    
    acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
        "commit data to cached file");
    return 0;
}

void AcdCallDataCollection::commit_data()
{
    string cur_date = bgcc::TimeUtil::get_date();
    uint64_t cur_second = bgcc::TimeUtil::get_timestamp_s();
    const static uint64_t time_interval = 30;
    if (cur_date != _cached_date) {
        reset();
        put_data_to_file();
        acd_tool::m_logger.WriteLog(LOG_LEVEL_NOTICE, __FILE__, __LINE__, __FUNCTION__,
            "not this day, put data to file");
    }
    if (cur_second - _cached_second > time_interval) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
            "commit data to file");
        put_data_to_file();
        _cached_second = cur_second;
    }
    _cached_date = cur_date;
}

void AcdCallDataCollection::update_data(calldata_ptr& callinfo)
{
    SingleRWLocker s(&_lock, true);
    if (callinfo.get() == NULL) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_NOTICE, __FILE__, __LINE__, __FUNCTION__,
            "callinfo is NULL");
        return;
    }
    uint32_t calltime = callinfo->m_callend - callinfo->m_callbegin;
    if (callinfo->m_callend < callinfo->m_callbegin) {
        calltime = 0;
    }
    uint32_t alerting = callinfo->m_ackend - callinfo->m_ackbegin;
    if (callinfo->m_ackend < callinfo->m_ackbegin) {
        alerting = 0;
    }
    //update cc info
    if (callinfo->m_callDirect.get_value() == CallDirectT::OUTBOUND) {
        ++_cc_call_data.outbound_call_num;
        if (calltime > 0) {
            ++_cc_call_data.outbound_ans_num;
            _cc_call_data.outbound_call_time += calltime;
        }
    }
    else if (callinfo->m_callDirect.get_value() == CallDirectT::INBOUND && calltime > 0) {
        ++_cc_call_data.inbound_call_num;
        _cc_call_data.inbound_alerting_time += alerting;
        if (calltime > 0) {
            ++_cc_call_data.inbound_ans_num;
            _cc_call_data.inbound_call_time += calltime;
        }
    }
    //update skill info
    if (callinfo->m_callDirect.get_value() == CallDirectT::INBOUND && !callinfo->m_skill.empty()) {
        iter iter = _skill_call_info.find(callinfo->m_skill);
        if (iter == _skill_call_info.end()) {
            acd_tool::m_logger.WriteLog(LOG_LEVEL_NOTICE, __FILE__, __LINE__, __FUNCTION__,
                "new skill (%s)", callinfo->m_skill.c_str());
            SkillCallData * p = new (std::nothrow) SkillCallData;
            if (p ==  NULL) {
                acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                    "new skill call data info failed, skill(%s)", callinfo->m_skill.c_str());
                return;
            }
            p->inbound_alerting_time = 0;
            p->inbound_answer_num = 0;
            p->inbound_call_time = 0;
            p->inbound_call_num = 0;
            ++p->inbound_call_num;
            p->inbound_alerting_time += alerting;
            if (calltime > 0) {
                ++p->inbound_answer_num;
                p->inbound_call_time += calltime;
            }
            _skill_call_info.insert(std::make_pair(callinfo->m_skill, p));
        }
        else {
            iter->second->inbound_alerting_time += alerting;
            ++iter->second->inbound_call_num;
            if (calltime > 0) {
                ++iter->second->inbound_answer_num;
                iter->second->inbound_call_time += calltime;
            }
            acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                "update skill info skill(%s), calltime(%d), alerttime(%d)", 
                    callinfo->m_skill.c_str(), calltime, alerting);
        }
    }
    
}

void AcdCallDataCollection::Method()
{
    acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
        "acd data collection thread begin");
    const static int32_t timeout = 30;
    while (this->mIsLoop) {
        calldata_ptr callinfo;
        bool ret = _calldata_queue.UnBlockPop(callinfo, timeout);
        commit_data();
        if (ret) {
            update_data(callinfo);
        }
    }
}

int32_t AcdCallDataCollection::get_call_data_by_plat(string& data)
{
    SingleRWLocker s(&_lock, true);
    string fail_str = "{\"result\":\"-1\",\"data\":\"memory error\"}";
    json_object *root = json_object_new_object();
    if (root == NULL) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
            "new root json object failed");
        data = fail_str;
        return -1;
    }
    json_object *calldata = json_object_new_object();
    if (calldata == NULL) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
            "new calldata json object failed");
        data = fail_str;
        json_object_put(root);
        return -1;
    }
    json_object_object_add(calldata, "OutCallNum", json_object_new_int(_cc_call_data.outbound_call_num));
    json_object_object_add(calldata, "OutAnsNum", json_object_new_int(_cc_call_data.outbound_ans_num));
    json_object_object_add(calldata, "OutCallTime", json_object_new_int(_cc_call_data.outbound_call_time));
    json_object_object_add(calldata, "InAnsNum", json_object_new_int(_cc_call_data.inbound_ans_num));
    json_object_object_add(calldata, "InCallNum", json_object_new_int(_cc_call_data.inbound_ans_num));
    json_object_object_add(calldata, "InCallTime", json_object_new_int(_cc_call_data.inbound_call_time));
    json_object_object_add(calldata, "InAlertTime", json_object_new_int(_cc_call_data.inbound_alerting_time));
    json_object_object_add(root, "result", json_object_new_string("0"));
    json_object_object_add(root, "data", calldata);
    data = json_object_to_json_string(root);
    //acd_tool::m_logger.WriteLog(LOG_LEVEL_NOTICE, __FILE__, __LINE__, __FUNCTION__,
    //    "get cc call data success, data(%s)", data.c_str());
    acd_tool::m_logger.WriteLog(LOG_LEVEL_NOTICE, __FILE__, __LINE__, __FUNCTION__,
        "get cc call data success");
    json_object_put(root);
    return 0;
}

int32_t AcdCallDataCollection::get_call_data_by_skill(string& data, const string& skill)
{
    SingleRWLocker s(&_lock, true);
    string fail_str = "{\"result\":\"-1\",\"data\":\"memory error\"}";
    json_object *root = json_object_new_object();
    if (root == NULL) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
            "new root json object failed");
        data = fail_str;
        return -1;
    }
    json_object *calldata = json_object_new_object();
    if (calldata == NULL) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
            "new calldata json object failed");
        data = fail_str;
        json_object_put(root);
        return -1;
    }
    iter iter = _skill_call_info.find(skill);
    if (iter == _skill_call_info.end()) {
        json_object_object_add(root, "result", json_object_new_string("-1"));
        json_object_object_add(root, "data", json_object_new_string("not found skill"));
        data = json_object_to_json_string(root);
        acd_tool::m_logger.WriteLog(LOG_LEVEL_NOTICE, __FILE__, __LINE__, __FUNCTION__,
            "get cc call data by skill failed, skill(%s)", skill.c_str());
        json_object_put(calldata);
        json_object_put(calldata);
        return -1;
    }
    json_object_object_add(calldata, "InCallTime", json_object_new_int(iter->second->inbound_call_time));
    json_object_object_add(calldata, "InAlertTime", json_object_new_int(iter->second->inbound_alerting_time));
    json_object_object_add(calldata, "InAnsNum", json_object_new_int(iter->second->inbound_answer_num));
    json_object_object_add(calldata, "InCallNum", json_object_new_int(iter->second->inbound_call_num));
    json_object_object_add(root, "result", json_object_new_string("0"));
    json_object_object_add(root, "data", calldata);
    data = json_object_to_json_string(root);
    //acd_tool::m_logger.WriteLog(LOG_LEVEL_NOTICE, __FILE__, __LINE__, __FUNCTION__,
    //    "get call data by skill success, skill(%s), data(%s)", skill.c_str(), data.c_str());
    acd_tool::m_logger.WriteLog(LOG_LEVEL_NOTICE, __FILE__, __LINE__, __FUNCTION__,
        "get call data by skill success skill(%s)", skill.c_str());
    json_object_put(root);
    return 0;
}

int32_t AcdCallDataCollection::get_call_data_by_all(string& data)
{
    SingleRWLocker s(&_lock, true);
    string fail_str = "{\"result\":\"-1\",\"data\":\"memory error\"}";
    json_object *root = json_object_new_object();
    if (root == NULL) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
            "new root json object failed");
        data = fail_str;
        return -1;
    }
    json_object *calldata = json_object_new_object();
    if (calldata == NULL) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
            "new calldata json object failed");
        data = fail_str;
        json_object_put(root);
        return -1;
    }
    // add plat call info
    json_object *platdata = json_object_new_object();
    if (calldata == NULL) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
            "new platdata json object failed");
        data = fail_str;
        json_object_put(root);
        json_object_put(calldata);
        return -1;
    }
    json_object_object_add(platdata, "OutCallNum", json_object_new_int(_cc_call_data.outbound_call_num));
    json_object_object_add(platdata, "OutAnsNum", json_object_new_int(_cc_call_data.outbound_ans_num));
    json_object_object_add(platdata, "OutCallTime", json_object_new_int(_cc_call_data.outbound_call_time));
    json_object_object_add(platdata, "InAnsNum", json_object_new_int(_cc_call_data.inbound_ans_num));
    json_object_object_add(platdata, "InCallNum", json_object_new_int(_cc_call_data.inbound_call_num));
    json_object_object_add(platdata, "InCallTime", json_object_new_int(_cc_call_data.inbound_call_time));
    json_object_object_add(platdata, "InAlertTime", json_object_new_int(_cc_call_data.inbound_alerting_time));
    json_object_object_add(calldata, "platinfo", platdata);
    json_object *skilldata = json_object_new_array();
    if (skilldata == NULL) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
            "new skilldata json object failed");
        data = fail_str;
        json_object_put(root);
        json_object_put(calldata);
        return -1;
    }
    for (iter iter = _skill_call_info.begin(); iter != _skill_call_info.end(); ++iter) {
        if (iter->second != NULL) {
            json_object *skillinfo = json_object_new_object();
            if (skillinfo == NULL) {
                acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                    "new skilinfo json object failed, skill(%s)", iter->first.c_str());
                continue;
            }
            json_object_object_add(skillinfo, "skillname", json_object_new_string(iter->first.c_str()));
            json_object_object_add(skillinfo, "InCallTime", json_object_new_int(iter->second->inbound_call_time));
            json_object_object_add(skillinfo, "InAlertTime", json_object_new_int(iter->second->inbound_alerting_time));
            json_object_object_add(skillinfo, "InAnsNum", json_object_new_int(iter->second->inbound_answer_num));
            json_object_object_add(skillinfo, "InCallNum", json_object_new_int(iter->second->inbound_call_num));
            json_object_array_add(skilldata, skillinfo);
        }
    }
    json_object_object_add(calldata, "skillinfo", skilldata);
    json_object_object_add(root, "result", json_object_new_string("0"));
    json_object_object_add(root, "data", calldata);
    data = json_object_to_json_string(root);
    //acd_tool::m_logger.WriteLog(LOG_LEVEL_NOTICE, __FILE__, __LINE__, __FUNCTION__,
    //    "get call data by ALL success, data(%s)", data.c_str());
    acd_tool::m_logger.WriteLog(LOG_LEVEL_NOTICE, __FILE__, __LINE__, __FUNCTION__,
        "get call data by ALL success");
    json_object_put(root);
    return 0;    
}

acd::AcdResultT AcdCallDataCollection::get_call_data(int64_t handle, const std::string& agentId,
                                                            int32_t type, const string& input, string& result)
{
    acd::AcdResultT ret = acd::AcdResultT::ArSuccess;
    if (agentId.empty()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__, "empty agentId");
        ret = acd::AcdResultT::ArAgentIdIsEmpty;
        return ret;
    }

    if (!acd_tool::p_m_acd_backup->GetIsMaster()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d not master", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArNotMaster;
        return ret;
    }
    if (type == GETBYPLAT) {
        return get_call_data_by_plat(result);
    }
    else if (type == GETBYSKILL) {
        return get_call_data_by_skill(result, input);
    }
    else if (type == GETALL) {
        return get_call_data_by_all(result);
    }
    return -1;
}

void AcdCallDataCollection::reset()
{
    SingleRWLocker s(&_lock, true);
    for (iter iter = _skill_call_info.begin()
            ; iter != _skill_call_info.end()
            ; ++iter) {
         if (iter->second != NULL) {
             delete iter->second;
             iter->second = NULL;
         }
         _skill_call_info.erase(iter->first);
    }

    _cc_call_data.inbound_ans_num = 0;
    _cc_call_data.inbound_call_num = 0;
    _cc_call_data.inbound_call_time = 0;
    _cc_call_data.outbound_ans_num = 0;
    _cc_call_data.outbound_call_num = 0;
    _cc_call_data.outbound_call_time = 0;
}

int32_t AcdCallDataCollection::push_call_data(calldata_ptr& calldata)
{
    if (calldata.get() == NULL ) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
            "calldata is NULL");
        return -1;
    }
    _calldata_queue.BlockPush(calldata);
    acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
        "calldata has in queue, agentId(%s),  sessionid(%lu), callid(%s), skill(%s)",
        calldata->m_agentId.c_str(), calldata->m_sessionId, 
        calldata->m_callId.c_str(), calldata->m_skill.c_str());
    return 0;
}
};
