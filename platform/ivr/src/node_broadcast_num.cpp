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

#include "tools.h"
#include "node_broadcast_num.h"
#include "fs_opr.h"
#include "fs_mgr.h"

namespace ivr {

NodeBroadcastNum::NodeBroadcastNum(const uint32_t id, const string& name,
                                   const string& type, const string& desc, const key_map_t& keymap)
    : NodeResource(id, name, type, desc, keymap) {
    _delay = 0;
}

NodeBroadcastNum::~NodeBroadcastNum(void) {
}

NodeBase* NodeBroadcastNum::run(base_script_t* param) {
    if (NULL == param) {
        IVR_WARN("base_script_t pointer should not be null");
        return NULL;
    }

    const char* exit = EXIT_FAIL;
    std::string ret = "";
    IVR_TRACE("%s", enter(param->name_var_map).c_str());

    if (_delay != 0) {
        ivr_tools_t::safe_sleeps(_delay);
    }

    std::string playstr;
    std::string callid1;
    std::string callid2;
    fs_opr_t* opr = NULL;
    fw_id_t fs_no;

    if (parse_expression(_callid1, param->name_var_map, callid1)
            && parse_expression(_callid2, param->name_var_map, callid2)
            && parse_expression(_play_str, param->name_var_map, playstr)) {
        IVR_TRACE("callid1=%s,callid2=%s,delay=%u,playstr=%s",
                  callid1.c_str(), callid2.c_str(),  _delay, playstr.c_str());
    }  else {
        IVR_WARN("parse callid or playstr failed");
        IVR_TRACE("%s exit from %s(%s)",
                  leave(param->name_var_map).c_str(), exit, ret.c_str());
        return _exit_node_map[exit];
    }

    if (!ivr_tools_t::is_all_digit(playstr)) {
        IVR_TRACE("放音字符串不均为数字[%s]", playstr.c_str());
        IVR_TRACE("%s exit from %s(%s)",
                  leave(param->name_var_map).c_str(), exit, ret.c_str());
        return _exit_node_map[exit];
    }

    fs_no = param->fid;

    if (fs_mgr_t::instance()->fetch_opr(fs_no, &opr) == IVR_SUCCESS) {
        if (NULL != opr) {
            if (0 == strcasecmp(_playtype.c_str(), _s_paramitem_number)) {
                if (opr->broadcast_num(callid1.c_str(), callid2.c_str(), playstr.c_str(),
                                       param->vox_base.c_str(), true) == IVR_SUCCESS) {
                    exit = EXIT_SUCC;
                } else {
                    IVR_WARN("opr playnum err(callid1:%s,callid2:%s,number: %s)",
                             callid1.c_str(), callid2.c_str(), playstr.c_str());
                }
            } else if (0 == strcasecmp(_playtype.c_str(), _s_paramitem_int32)) {
                if (opr->broadcast_num(callid1.c_str(), callid2.c_str(), playstr.c_str(),
                                       param->vox_base.c_str(), false) == IVR_SUCCESS) {
                    exit = EXIT_SUCC;
                } else {
                    IVR_WARN("opr broadcastnum err(callid1:%s,callid2:%s,number: %s)",
                             callid1.c_str(), callid2.c_str(), playstr.c_str());
                }
            } else {
                IVR_WARN("invalid playtype");
            }
        } else {
            IVR_WARN("fs_opr_t pointer should not be null");
        }

        fs_mgr_t::instance()->free_opr(&opr);
    } else {
        IVR_WARN("fetch opr failed. freeswitch no is %d", fs_no);
    }

    IVR_TRACE("%s exit from %s(%s)",
              leave(param->name_var_map).c_str(), exit, ret.c_str());

    return _exit_node_map[exit];
}

bool NodeBroadcastNum::load_other() {
    std::string tmp;

    if (!valid_str(_key_map, _s_param_callid1, _callid1)) {
        return false;
    }

    if (!valid_str(_key_map, _s_param_callid2, _callid2)) {
        return false;
    }

    valid_str(_key_map, _s_param_str, _play_str);//允许为空

    //延时时间设置
    _delay = 0;

    if (valid_str(_key_map, _s_param_delay, tmp)) {//允许为空
        if (ivr_tools_t::is_positive_integer(tmp)) {
            _delay = atoi(tmp.c_str());
        }
    }

    //playtype初始化
    _playtype = _s_paramitem_number;

    if (valid_str(_key_map, _s_param_playtype, tmp)) {
        if (0 == strcasecmp(_playtype.c_str(), _s_paramitem_number)
                || 0 == strcasecmp(_playtype.c_str(), _s_paramitem_int32)) {
            _playtype = tmp;
        }
    }

    return NodeBase::load_other();
}

const char* NodeBroadcastNum::_s_param_delay = "delay";
const char* NodeBroadcastNum::_s_param_str = "playstr";
const char* NodeBroadcastNum::_s_param_callid1 = "callid1";
const char* NodeBroadcastNum::_s_param_callid2 = "callid2";
const char* NodeBroadcastNum::_s_param_playtype = "playtype";
const char* NodeBroadcastNum::_s_paramitem_number = "number";
const char* NodeBroadcastNum::_s_paramitem_int32 = "int32";

std::string NodeBroadcastNum::enter(const map<string, variable_t>& vars) const {
    ostringstream ostm;
    ostm << NodeBase::enter(vars);
    ostm << "file:" << _play_str << ",delay:" << _delay;
    return ostm.str();
}

}
