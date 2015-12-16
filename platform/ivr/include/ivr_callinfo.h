// Copyright (c) 2015 Baidu.com, Inc. All Rights Reserved
// author liuqiang(liuqiang06@baidu.com)

// ivr call info define

#ifndef APP_ECOM_CCSERVICE_CALLCLOUD_IVR_INCLUDE_IVR_CALLINFO_H
#define APP_ECOM_CCSERVICE_CALLCLOUD_IVR_INCLUDE_IVR_CALLINFO_H

#include "common.h"

namespace ivr {
class ReleaseCauseT {
public:
    enum {
        UNKNOWN,
        THISPARTY,
        OTHERPARTY
    };

private:
    int _m_value;
public:
    ReleaseCauseT(int32_t value);
    ~ReleaseCauseT();
    void set_value(int32_t value);
    int32_t get_value();
    bool isValid();
};

class IvrCallInfo 
{
public:
    IvrCallInfo();
    ~IvrCallInfo();
    void initial(ivr_session_id_t sessionId, const std::string& caller, const std::string& callee);
    std::string get_callee();
    void set_inbound_begin_time(time_t t);
    time_t get_inbound_begin_time();
    void set_flow_begin_time(time_t t);
    void set_cust_ans_time(time_t t);
    void set_agt_ans_time(time_t t);
    void set_agt_alert_time(time_t t);
    void set_connected_time(time_t t);
    void set_trans_time(time_t t);
    void set_hangup_time(time_t t);
    void set_exit_flow_time(time_t t);
    void set_release_cause(int32_t releaseCause);
    void set_record_filename(const string &recordFilename);
    void set_skill(const std::string& skill);
    std::string get_skill();
    void set_agent_num(const string &agentnum);
    void reset();
    void write_call_log();
private:
    ivr_session_id_t _m_sessionid;
    string _m_skill;
    string _m_caller;
    string _m_callee;
    time_t _m_inboundbegin_time;
    time_t _m_flowbegin_time;
    time_t _m_cust_ans_time;
    time_t _m_agt_ans_time;
    time_t _m_agt_alert_time;
    time_t _m_connected_time;
    time_t _m_trans_time;
    time_t _m_exit_flow_time;
    time_t _m_hangup_time;
    string _m_agentnum;
    ReleaseCauseT _m_releaseCause;
    string _m_recordFilename;
};
};
#endif
