/*
 * Copyright 2002-2014 the original author or authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      CC/LICENSE
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#pragma once

#include "const_define.h"

using namespace std;

class CallDirectT {
public:
    enum {
        UNKNOWN,
        INBOUND,
        OUTBOUND
    };

private:
    int m_value;

public:
    CallDirectT(int32_t value);
    ~CallDirectT();
    void set_value(int32_t value);
    int32_t get_value();
    bool isValid();
};

class ReleaseCauseT {
public:
    enum {
        UNKNOWN,
        THISPARTY,
        OTHERPARTY
    };

private:
    int m_value;

public:
    ReleaseCauseT(int32_t value);
    ~ReleaseCauseT();
    void set_value(int32_t value);
    int32_t get_value();
    bool isValid();
};

struct calldata {
public:
    calldata() : m_sessionId(0), m_callId(""), m_agentId(""), m_agentDn(""), m_caller(""),
    m_callee(""), m_waitbegin(0), m_waitend(0), m_ackbegin(0), m_ackend(0), 
    _m_connectbegin(0), _m_connectend(0), m_callbegin(0), m_callend(0),
    m_callType(ims::PartyAttributeT::P_Unknown), m_callDirect(CallDirectT::UNKNOWN),
    m_releaseCause(ReleaseCauseT::UNKNOWN),
    m_recordFilename(""), m_routecall(false){}

    calldata(ims::SessionIdT sessionId, ims::CallIdT callId, string agentId, string agentDn,
    string skill, string caller, string callee, time_t waitbegin, time_t waitend, time_t ackbegin,
    time_t ackend, time_t connectbegin, time_t connectend, time_t callbegin,
    time_t callend, ims::PartyAttributeT callType, CallDirectT callDirect, 
    ReleaseCauseT releaseCause, string recordFilename, bool routecall)
    : m_sessionId(sessionId), m_callId(callId), m_agentId(agentId), m_agentDn(agentDn), 
    m_skill(skill), m_caller(caller),
    m_callee(callee), m_waitbegin(waitbegin), m_waitend(waitend), m_ackbegin(ackbegin), m_ackend(ackend), 
    _m_connectbegin(connectbegin), _m_connectend(connectend), m_callbegin(callbegin), m_callend(callend),
    m_callType(callType), m_callDirect(callDirect),
    m_releaseCause(releaseCause), m_recordFilename(recordFilename), m_routecall(routecall){}

public:
    ims::SessionIdT m_sessionId;
    ims::CallIdT m_callId;
    string m_agentId;
    string m_agentDn;
    string m_skill;
    string m_caller;
    string m_callee;

    time_t m_waitbegin;
    time_t m_waitend;
    time_t m_ackbegin;
    time_t m_ackend;
    time_t _m_connectbegin;//other altering begin
    time_t _m_connectend;//other alerting end
    time_t m_callbegin;
    time_t m_callend;

    ims::PartyAttributeT m_callType;
    CallDirectT m_callDirect;
    ReleaseCauseT m_releaseCause;
    string m_recordFilename;

    bool m_routecall;
};

typedef bgcc::SharedPtr<calldata> calldata_ptr;

class callinfo : private calldata{
public:
    callinfo();
    ~callinfo();
    void Initial(ims::SessionIdT sessionId, const ims::CallIdT& callId, const string& agentId,
                 const string& agentDn, const string& skill, const string& caller, const string& callee,
                 time_t waitbegin, time_t waitend);
    void SetAniDnis(const string& caller, const string& callee);
    void SetAckBegin(time_t t);
    void SetAckEnd(time_t t);
    void SetConnectBegin(time_t t);
    void SetConnectEnd(time_t t);
    void SetCallBegin(time_t t);
    void SetCallEnd(time_t t);
    void SetCallType(const ims::PartyAttributeT& callType);
    void SetCallDirect(int32_t callDirect);
    void SetReleaseCause(int32_t releaseCause);
    void SetRecordFilename(const string& recordFilename);
    void SetRoutecall();
    bool GetRoutecall();
    bool isValid();
    void reset();
    void WriteCallLog();
    void AddDataToCollection();
};
