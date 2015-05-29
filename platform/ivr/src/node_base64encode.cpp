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

#include "node_base64encode.h"

NodeBase64Encode::NodeBase64Encode(const uint32_t id, const string& name,
                       const string& type, const string& desc, const key_map_t& keymap)
    : NodeBase(id, name, type, desc, keymap) {
}

NodeBase64Encode::~NodeBase64Encode(void) {
}

std::string base64_encode(const std::string& input)
{
    static const char base64_chars[] = 
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    
    std::string result;
    
    int i = 0;
    unsigned char char_array_3[3];
    
    const unsigned char* bytes_to_encode = (const unsigned char*)input.c_str();
    size_t in_len = input.size();
    
    result.reserve(((in_len + 2) / 3) * 4);
    while (in_len--)
    {
        char_array_3[i++] = *(bytes_to_encode++);
        if (i == 3)
        {
            result.push_back(base64_chars[(char_array_3[0] & 0xfc) >> 2]);
            result.push_back(base64_chars[((char_array_3[0] & 0x03) << 4) + 
                    ((char_array_3[1] & 0xf0) >> 4)]);
            result.push_back(base64_chars[((char_array_3[1] & 0x0f) << 2) + 
                    ((char_array_3[2] & 0xc0) >> 6)]);
            result.push_back(base64_chars[char_array_3[2] & 0x3f]);
            
            i = 0;
        }
    }
    
    if (i != 0)
    { // input.size() % 3 != 0
        memset(char_array_3 + i, 0, 3 - i);
        result.push_back(base64_chars[(char_array_3[0] & 0xfc) >> 2]);
        result.push_back(base64_chars[((char_array_3[0] & 0x03) << 4) + 
                ((char_array_3[1] & 0xf0) >> 4)]);
        if (i >= 2){
            result.push_back(base64_chars[((char_array_3[1] & 0x0f) << 2) + 
                ((char_array_3[2] & 0xc0) >> 6)]);
        }
        else result.push_back('=');
        result.push_back('=');
    }
    
    return result;
}

NodeBase* NodeBase64Encode::run(base_script_t* param) {
    const char* exit = EXIT_FAIL;
    std::string ret = "";
    std::string tmp = "";
    IVR_TRACE("%s", enter(param->name_var_map).c_str());

    map<string, variable_t>::iterator it = param->name_var_map.find(_result);

    if (it == param->name_var_map.end()) {
        IVR_WARN("未找到返回值变量");
    } else {
        if (parse_expression(_input, param->name_var_map, ret)) {

            if (STRING != it->second.type) {
                IVR_WARN("变量%s 的类型不能被编码", _result.c_str());
            } else {
                tmp = base64_encode(ret);
                *(string*)it->second.pvalue = tmp;
                exit = EXIT_SUCC;
            }
        } else {
            IVR_WARN("parse assign expression failed(%s)", _input.c_str());
        }
    }

    IVR_TRACE("%s exit from %s(%s)",
              leave(param->name_var_map).c_str(), exit, tmp.c_str());
    return _exit_node_map[exit];
}

bool NodeBase64Encode::load_other() {
    return NodeBase::load_other()
           && valid_str(_key_map, _s_param_input, _input, false)
           && valid_str(_key_map, _s_param_result, _result);
}

const char* NodeBase64Encode::_s_param_input = "input";
const char* NodeBase64Encode::_s_param_result = "result";

std::string NodeBase64Encode::enter(const map<string, variable_t>& vars)const {
    ostringstream ostm;
    ostm << NodeBase::enter(vars);
    ostm << "input:" << _input << ",result:" << _result;
    return ostm.str();
}

std::string NodeBase64Encode::leave(const map<string, variable_t>& vars)const {
    ostringstream ostm;
    ostm << NodeBase::leave(vars);
    ostm << "result:" << _result;
    return ostm.str();
}


