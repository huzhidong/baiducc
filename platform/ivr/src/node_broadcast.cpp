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
#include "node_broadcast.h"
#include "fs_opr.h"
#include "fs_mgr.h"

namespace ivr {

NodeBroadcast::NodeBroadcast(const uint32_t id, const string& name,
                             const string& type, const string& desc, const key_map_t& keymap)
    : NodeResource(id, name, type, desc, keymap) {
    _delay = 0;
}

NodeBroadcast::~NodeBroadcast(void) {
}

NodeBase* NodeBroadcast::run(base_script_t* param) {
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

    std::string playfile;
    std::string callid1;
    std::string callid2;
    fs_opr_t* opr = NULL;
    fw_id_t fs_no;

    if (parse_expression(_callid1, param->name_var_map, callid1)
            && parse_expression(_callid2, param->name_var_map, callid2)
            && parse_expression(_play_file, param->name_var_map, playfile)) {
        IVR_TRACE("callid1=%s, callid2=%s, delay=%u,playfile=%s",
                  callid1.c_str(), callid2.c_str(),  _delay, (param->vox_base + playfile).c_str());
        playfile = param->vox_base + playfile;
    }  else {
        IVR_WARN("parse callid or playfile failed");
        goto END;
    }

    fs_no = param->fid;

    if (fs_mgr_t::instance()->fetch_opr(fs_no, &opr) == IVR_SUCCESS) {
        if (NULL != opr) {
            if (opr->uuid_broadcast(callid1.c_str(), callid2.c_str(),
                                    playfile.c_str()) == IVR_SUCCESS) {
                exit = EXIT_SUCC;
            } else {
                IVR_WARN("opr broadcast  failed(callid1: %s, callid2:%s)",
                         _callid1.c_str(), _callid2.c_str());
            }
        } else {
            IVR_WARN("fs_opr_t pointer should not be null");
        }

        fs_mgr_t::instance()->free_opr(&opr);
    } else {
        IVR_WARN("fetch opr failed. freeswitch no is %d", fs_no);
    }

END:
    NodeBase* exit_node_ptr = NULL;
    std::map<std::string, NodeBase*>::iterator citr;
    citr = _exit_node_map.find(exit);

    if (citr != _exit_node_map.end()) {
        exit_node_ptr = citr->second;
        IVR_TRACE("%s exit from %s(%s)",
                  leave(param->name_var_map).c_str(), exit, ret.c_str());
    } else {
        IVR_WARN("Can not find exit %s in _exit_node_map", exit);
    }

    return exit_node_ptr;
}

bool NodeBroadcast::load_other() {
    std::string tmp;

    if (!valid_str(_key_map, _s_param_callid1, _callid1)) {
        return false;
    }

    if (!valid_str(_key_map, _s_param_callid2, _callid2)) {
        return false;
    }

    valid_str(_key_map, _s_param_file, _play_file);//允许为空

    _delay = 0;

    if (valid_str(_key_map, _s_param_delay, tmp)) {//允许为空
        if (ivr_tools_t::is_positive_integer(tmp)) {
            _delay = atoi(tmp.c_str());
        }
    }

    return  NodeBase::load_other();
}
//const char * NodeBroadcast::PARAM_CALLID="callid";
const char* NodeBroadcast::_s_param_delay = "delay";
const char* NodeBroadcast::_s_param_file = "playfile";
const char* NodeBroadcast::_s_param_callid1 = "callid1";
const char* NodeBroadcast::_s_param_callid2 = "callid2";

std::string NodeBroadcast::enter(const map<string, variable_t>& vars) const {
    ostringstream ostm;
    ostm << NodeBase::enter(vars);
    ostm << ",delay:" << _delay << ",file:" << _play_file;
    return ostm.str();
}

}
