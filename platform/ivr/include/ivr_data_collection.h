/*
 * Copyright 2002-2015 the original author or authors.
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

// ivr data collection define

#ifndef _IVR_DATA_COLLECTION_H
#define _IVR_DATA_COLLECTION_H

#include "ivr_callinfo.h"
#include "fs_struct.h"

namespace ivr {
// Ã¿¸ö¼¼ÄÜ×éµÄĞÅÏ¢
struct SkillCallData{
public:
    SkillCallData() : giveuptimes(0){}
public:
    uint32_t giveuptimes;  // ¸Ã¼¼ÄÜ×éµÄÅÅ¶Ó·ÅÆúÁ¿
};

// µ±Ç°µÄºô½ĞÊı¾İºô½ĞÊı¾İ
struct IvrCallData{
public:
    IvrCallData()
    : cur_inbound_num(0)
    , cur_accept_num(0)
    , trans_num(0)
    , total_inbound_num(0)
    , total_accept_num(0)
    , giveuptimes(0){}
public:
    uint32_t cur_inbound_num;  // µ±Ç°ºôÈë×ÜÁ¿
    uint32_t cur_accept_num;  // µ±Ç°»îÔ¾µÄºôÈëÁ¿
    uint32_t trans_num;  //×ª×øÏ¯Á¿
    uint32_t total_inbound_num;  // ×ÜºôÈë×ÜÁ¿
    uint32_t total_accept_num;  // ×Ü»îÔ¾µÄºôÈëÁ¿
    uint32_t giveuptimes; // ÅÅ¶Ó·ÅÆúÁ¿
    std::map<std::string, SkillCallData*> skill_call_data; //¼¼ÄÜºô½ĞÊı¾İ
};

class IvrInboundCall {
public:
    enum {
        BEGIN,
        ACCEPT,
        INFLOW,
        CUSTOMERANSWER,
        AGENTALERTING,
        AGENTANSWER,
        CONNECTED,
        ROUTEBYSKILL,
        ROUTEBYAGENTID,
        ROUTEBYAGENTLIST,
        TRANSAGENT,
        EXITFLOW,
        CALLWITHOUTFOLW,
        THISPARTYHANGUP,
        OTHERPARTYHANGUP,
        UNKNOW
    }; // state

    IvrInboundCall() : _m_state(UNKNOW), _has_hangup(false), _exit_flow(false){}
    ~IvrInboundCall(){}
    int32_t update_route_skill_endtime(const std::string& skill_name);
    int32_t set_appdata(const std::string& appdata);
    int32_t set_state(int32_t state);//ÉèÖÃµ±Ç°×´Ì¬
    int32_t get_state();//ÉèÖÃµ±Ç°×´Ì¬
    void init_new_call(const ivr_session_id_t& sessionId, const string &callid, const string &caller, const string &callee); 
    void set_skill(const std::string& skill);
    std::string get_skill();
    std::string get_called();
    bool get_exit_flow();
    void set_agent_num(const string &agentnum);
    time_t get_begintime();
private:
    int32_t _m_state;
    bool _has_hangup;
    bool _exit_flow;
    IvrCallInfo _m_ivr_callinfo;
} ;

class IvrCallDataCollection
{
public:
    enum {
        GETBYPLAT,
        GETBYIVRNUM,
    };

    IvrCallDataCollection(){}
private:
    ~IvrCallDataCollection(){}
public:
    static IvrCallDataCollection& instance();

    // @breif ³õÊ¼»¯º¯Êı
    int32_t initialize(const char* path);
    
    // @breif ·´ ³õÊ¼»¯º¯Êı
    int32_t uninitialize();
    
    // ½«Êı¾İĞ´ÈëÎÄ¼şÇÒÅĞ¶ÏÈÕÆÚº¯Êı
    void calldata_to_file_block_func();
    
    // @brief ºôÈëÁ¿(½øÈëÁ÷³Ì) +1
    // @param caller ºôÈëºÅÂë
    // @param called ivr×ª½ÓÂë
    // @parma sessionid ,±ê¼ÇÃ¿Í¨ºô½ĞÌ
    // @return 0:success other:failed
    int32_t new_accept_call(const std::string& caller, const std::string& called
                    , const ivr_session_id_t& sessionId, const std::string& uuid);

    // @brief ºôÈëÁ¿(ËùÓĞµÄÁ¿) +1
    // @param caller ºôÈëºÅÂë
    // @param called ivr×ª½ÓÂë
    // @parma uuit uuid,±ê¼ÇÃ¿Í¨ºô½ĞÌ
    // @return 0:success other:failed
    int32_t new_inbound_call(const std::string& caller, const std::string& called
                    , const std::string& uuid);
    
    // @brief ÉèÖÃ×´Ì¬
    // @parma callid callid,±ê¼ÇÃ¿Í¨ºô½Ğ
    // @parma state ×´Ì¬ 
    // @parma skill ¼¼ÄÜ£¬Ä¬ÈÏÎª¿Õ
    // @return 0:success other:failed   
    int32_t set_appdata(const ivr_session_id_t& sessionId, const std::string& appdata);
    int32_t set_state(const ivr_session_id_t& sessionId, const int32_t state, const std::string& skill);
    
    // @brief ´¦ÀíÊÂ¼ş
    // @parma event,ÊÂ¼ş
    // @return 0:success other:failed
    int32_t process_event(struct fs_event& event);

    // @brief ´¦ÀíÂ·ÓÉÊÂ¼şºÍ³¬Ê±ÊÂ¼ş
    // @parma event,ÊÂ¼ş
    // @return 0:success other:failed
    int32_t process_event(ivr_base_event_t* event);
    
    // @breif »ñÈ¡ÏµÍ³µ±Ç°ºô½ĞÊı¾İ
    // @param calldata calldataµØÖ·
    // @param result ·µ»ØµÄ¼¼ÄÜ×éÊı¾İ
    // @return 0:success other:failed  
    int32_t get_call_data(struct IvrCallData* p, std::string& result);
    
    // @breif »ñÈ¡ÏµÍ³µ±Ç°ºô½ĞÊı¾İ
    // @param result ·µ»ØµÄ¼¼ÄÜ×éÊı¾İ
    // @return 0:success other:failed  
    int32_t get_inbound_by_plat(std::string& result);

    // @breif »ñÈ¡ÏµÍ³µ±Ç°ºô½ĞÊı¾İ
    // @param result ·µ»ØµÄ¼¼ÄÜ×éÊı¾İ
    // @return 0:success other:failed  
    int32_t get_inbound_call_data(const int32_t type, const std::string& input, std::string& result);
    
    // @breif »ñÈ¡ÏµÍ³µ±Ç°ºô½ĞÊı¾İ
    // @param ivrnum ivr½ÓÈëÂë
    // @param result ¸ù¾İivr½ÓÈëÂë·µ»ØÊı¾İ
    // @return 0:success other:failed  
    int32_t get_inbound_by_ivrnum(const std::string& ivrnum, std::string& result);

    // @brief ´ÓÎÄ¼şÖĞ»ñÈ¡»º´æÊı¾İ
    int32_t get_data_from_file();

    // @brief ½«»º´æÊı¾İĞ´ÈëÎÄ¼şÖĞ
    int32_t put_data_to_file();

    // @ÅĞ¶ÏÊÇ·ñÅÅ¶Ó·ÅÆú£¬Èç¹ûÊÇ¸üĞÂÏà¹ØÊı¾İ
    int32_t is_giveup_call(IvrInboundCall *call
                    , const uint64_t sessionid, const std::string& called);

    // @brief ¸´Î»
    void clear_invaid_call();
    
    // @brief ¸´Î»
    void reset();

private:
    bgcc::Mutex _m_locker;
    std::string _cached_file; // »º´æÎÄ¼şÂ·¾¶
    std::string _cached_date; // »º´æÈÕÆÚ
    struct IvrCallData _plat_call_data;//µ±Ç°µÄºô½ĞÊı¾İ
    std::map<std::string, struct IvrCallData*> _ivrnum_call_data; // °´ivr½ÓÈëÂë´æ´¢µÄµ±Ììºô½ĞÊı¾İ
    std::map<ivr_session_id_t, IvrInboundCall*> _realtime_call;
    std::map<ivr_session_id_t, IvrInboundCall*> _exitflow_call;
    std::map<std::string, ivr_session_id_t> _first_uuid_map;
    std::map<std::string, ivr_session_id_t> _second_uuid_map;
    std::set<std::string> _refuse_call;
};

typedef std::map<std::string, struct SkillCallData*>::iterator IterSkill;
typedef std::map<std::string, struct IvrCallData*>::iterator IterIvrNum;
typedef std::map<ivr_session_id_t, IvrInboundCall*>::iterator IterCall;
typedef std::map<std::string, ivr_session_id_t>::iterator IterSession;
typedef std::set<std::string>::iterator IterStr;
}

#endif

