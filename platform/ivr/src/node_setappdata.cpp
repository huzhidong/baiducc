/*
 * Copyright 2002-2016 the original author or authors.
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

#include "node_setappdata.h"
#include "ivr_data_collection.h"

NodeSetAppData::NodeSetAppData(const uint32_t id, const string& name,
                         const string& type, const string& desc, const key_map_t& keymap)
    : NodeBase(id, name, type, desc, keymap) {
}

NodeSetAppData::~NodeSetAppData(void) {
}

NodeBase* NodeSetAppData::run(base_script_t* param) {
    const char* exit = EXIT_FAIL;
    std::string ret = "";
    IVR_TRACE("%s", enter(param->name_var_map).c_str());

    if (parse_expression(_app_data, param->name_var_map, ret)) {
        if (ret.length() > 512 || ret.find("\n", 0, ret.length() - 1) != std::string::npos) {
            exit = EXIT_FAIL;
			IVR_WARN("appdata is too long(%d)", int(ret.length()));
        } else {
            //to do set call data
            ivr::IvrCallDataCollection::instance().set_appdata(param->session_id, ret);
			exit = EXIT_SUCC;
        }
    } else {
        IVR_WARN("parse assign expression failed(%s)", _app_data.c_str());
    }
    IVR_TRACE("%s exit from %s",
              leave(param->name_var_map).c_str(), exit);
    return _exit_node_map[exit];
}

bool NodeSetAppData::load_other() {
    return NodeBase::load_other()
           && valid_str(_key_map, _s_param_input, _app_data);
}

const char* NodeSetAppData::_s_param_input = "appdata";

std::string NodeSetAppData::enter(const map<string, variable_t>& vars)const {
    ostringstream ostm;
    ostm << NodeBase::enter(vars);
    ostm << "appdata:" << _app_data;
    return ostm.str();
}

std::string NodeSetAppData::leave(const map<string, variable_t>& vars)const {
    ostringstream ostm;
    ostm << NodeBase::leave(vars);
    return ostm.str();
}

