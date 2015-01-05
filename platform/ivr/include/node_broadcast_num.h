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

#ifndef _NODE_BROADCAST_NUM_H
#define _NODE_BROADCAST_NUM_H


#include "node_resource.h"

namespace ivr {

class NodeBroadcastNum : public NodeResource {
public:
    NodeBroadcastNum(const uint32_t id, const string& name,
                     const string& type, const string& desc, const key_map_t& keymap);
    virtual ~NodeBroadcastNum(void);

    virtual NodeBase* run(base_script_t* param);

    virtual bool load_other();
private:

    string _callid1;
    string _callid2;
    string _play_str;
    uint32_t _delay;          ///< 开始放音的延时
    string _playtype;
    //const static char * PARAM_CALLID;
    const static char* _s_param_delay;       ///<
    const static char* _s_param_str;        ///<
    const static char* _s_param_callid1;        ///<
    const static char* _s_param_callid2;        ///<
    const static char* _s_param_playtype;
    const static char* _s_paramitem_number;
    const static char* _s_paramitem_int32;

    /**
     * @brief
     *
     * @param [in/out] map<string   : const
     * @param [in/out] vars   : variable_t>&
     * @return  std::string
     * @retval
     * @see
     * @note
     * @date 2014/06/18 10:08:22
    **/
    std::string enter(const map<string, variable_t>& vars) const;
};

}
#endif
