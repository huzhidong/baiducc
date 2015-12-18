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

#ifndef _NODE_BASE64ENCODE_H
#define _NODE_BASE64ENCODE_H

#include "node_base.h"

class NodeBase64Encode : public NodeBase {
public:
    NodeBase64Encode(const uint32_t id, const string& name,
               const string& type, const string& desc, const key_map_t& keymap);
    virtual ~NodeBase64Encode(void);

    virtual NodeBase* run(base_script_t* param);

    virtual bool load_other();

    virtual std::string enter(const map<string, variable_t>& vars)const ;

    virtual std::string leave(const map<string, variable_t>& vars)const ;
private:
    string _input;          ///ÊäÈëµÄÎ´±àÂë×Ö·û´®
    string _result;       ///´æ·Å±àÂëºóµÄ×Ö·û´®
    const static char* _s_param_input;
    const static char* _s_param_result;

};

#endif
