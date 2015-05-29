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

#include "node_base64decode.h"

NodeBase64Decode::NodeBase64Decode(const uint32_t id, const string& name,
                       const string& type, const string& desc, const key_map_t& keymap)
    : NodeBase(id, name, type, desc, keymap) {
}

NodeBase64Decode::~NodeBase64Decode(void) {
}

//////////////////////////////////////////////////////////////////////////////////////////
//Base64 解码
char getbase64value(char ch) //得到编码值
{
    if ((ch >= 'A') && (ch <= 'Z')){  // A ~ Z
        return ch - 'A';
    }
    if ((ch >= 'a') && (ch <= 'z')){  // a ~ z
        return ch - 'a' + 26;
    }
    if ((ch >= '0') && (ch <= '9')){  // 0 ~ 9
        return ch - '0' + 52;
    }
    switch (ch)       // 其它字符
    {
    case '+':
        return 62;
    case '/':
        return 63;
    case '=':  //Base64 填充字符
        return 0;
    default:
        return 0;
    }
}

// 解码函数
int32_t base64decode(std::string& OrgString, std::string& Base64String, int Base64StringLen, bool bForceDecode)  //解码函数
{
    OrgString = "";
    if (Base64StringLen % 4 && !bForceDecode)   //如果不是 4 的倍数,则 Base64 编码有问题
    {
        return -1;
    }
    unsigned char base64encode[4];
    char *p = new (std::nothrow)char[3];
    int32_t orgstringlen = 0;
    int32_t cur = 0;
    
    while (Base64StringLen > 3)  //当待解码个数不足3个时,将忽略它(强制解码时有效)
    {
        base64encode[0] = getbase64value(Base64String.at(cur));
        base64encode[1] = getbase64value(Base64String.at(cur + 1));
        base64encode[2] = getbase64value(Base64String.at(cur + 2));
        base64encode[3] = getbase64value(Base64String.at(cur + 3));
        
        *p = (base64encode[0] << 2) | (base64encode[1] >> 4);
        *(p + 1) = (base64encode[1] << 4) | (base64encode[2] >> 2);
        *(p + 2) = (base64encode[2] << 6) | (base64encode[3]);
        
        cur += 4;
        Base64StringLen -= 4;
        orgstringlen += 3;
        OrgString = OrgString + std::string(p).substr(0, 3);//delete "\0"
    }
    delete[] p;
    p = NULL;
    return orgstringlen;
}

NodeBase* NodeBase64Decode::run(base_script_t* param) {
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
                IVR_WARN("变量%s 的类型不能解码", _result.c_str());
            } else {
                if (base64decode(tmp, ret, ret.length(), true) > 0){
                    *(string*)it->second.pvalue = tmp;
                    exit = EXIT_SUCC;
                }
                else{
                    exit = EXIT_FAIL;
                }
            }
        } else {
            IVR_WARN("parse assign expression failed(%s)", _input.c_str());
        }
    }

    IVR_TRACE("%s exit from %s(%s)",
              leave(param->name_var_map).c_str(), exit, tmp.c_str());
    return _exit_node_map[exit];
}

bool NodeBase64Decode::load_other() {
    return NodeBase::load_other()
           && valid_str(_key_map, _s_param_input, _input, false)
           && valid_str(_key_map, _s_param_result, _result);
}

const char* NodeBase64Decode::_s_param_input = "input";
const char* NodeBase64Decode::_s_param_result = "result";

std::string NodeBase64Decode::enter(const map<string, variable_t>& vars)const {
    ostringstream ostm;
    ostm << NodeBase::enter(vars);
    ostm << "input:" << _input << ",result:" << _result;
    return ostm.str();
}

std::string NodeBase64Decode::leave(const map<string, variable_t>& vars)const {
    ostringstream ostm;
    ostm << NodeBase::leave(vars);
    ostm << "result:" << _result;
    return ostm.str();
}

