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

// acd manager define

#ifndef _ACD_DATA_COLLECTION_H
#define _ACD_DATA_COLLECTION_H

#include<fstream> 
#include "safe_queue.h"
#include "acd_info.h"
#include "bgcc.h"
#include "thread.h"
#include "locker.h"

typedef struct {
    uint32_t outbound_call_num; //呼出量
    uint32_t outbound_ans_num; //呼出接通量
    uint32_t inbound_ans_num; //呼入接通量
    uint32_t inbound_call_time; //呼入电话总时长
    uint32_t outbound_call_time; //呼出电话总时长
} CCCallData;

typedef struct {
    uint32_t inbound_call_time; //呼入通话时长
    uint32_t inbound_alerting_time; //呼入振铃时长
    uint32_t inbound_answer_num; //呼入接通量
} SkillCallData;

namespace acd {
class AcdCallDataCollection : public Thread {
public:
    AcdCallDataCollection(){}
    ~AcdCallDataCollection(){}

    enum {
        GETBYPLAT,
        GETBYSKILL,
        GETALL
    };
protected:
    virtual void Method();
public:
    typedef std::map<string, SkillCallData*>::iterator iter;
public:

    // @brief 初始化
    void initialize(const char* path);

    // @brief 反初始化
    void unInitialize();

    // @brief 从文件中获取缓存数据
    int32_t get_data_from_file();

    // @brief 将缓存数据写入文件中
    int32_t put_data_to_file();

    // @brief 根据时间同步 或者复位数据
    void commit_data();

    // @brief 更新数据
    // @param callinfo 话单数据
    void update_data(calldata_ptr& callinfo);

    // @breif 获取呼叫云的所有呼叫信息
    // @param calldata 按呼叫云返回的呼叫信息
    // @return 0:success other:failed   
    int32_t get_call_data_by_plat(string& data);

    // @breif 根据技能组获取呼叫信息
    // @param calldata 按技能组返回的呼叫信息
    // @param skill 技能组
    // @return 0:success other:failed    
    int32_t get_call_data_by_skill(string& data, const string& skill);

    // @breif 根据技能组获取呼叫信息
    // @return 0:success other:failed    
    int32_t get_call_data_by_all(string& data);

    // @breif 获取呼叫信息
    // @param type 数据类型
    // @param input 输入
    // @param result 返回结果
    // @return 0:success other:failed    
    acd::AcdResultT get_call_data(int64_t handle, const std::string& agentId,
                                int32_t type, const string& input, string& result);

    // @brief 复位
    void reset();

    // @breif 将话单数据加入队列
    // @param calldata 话单数据
    // @return 0:success other:failed    
    int32_t push_call_data(calldata_ptr& calldata);

private:
    bgcc::RWLock _lock;
    string _cached_file; // 缓存文件路径
    string _cached_date; // 缓存日期
    uint64_t _cached_second; //缓存的时间，秒为单位
    SafeQueue<calldata_ptr> _calldata_queue;
    std::map<string, SkillCallData*> _skill_call_info; //按技能组返回的呼叫信息
    CCCallData _cc_call_data; //当前的呼叫数据
};
};

#endif

