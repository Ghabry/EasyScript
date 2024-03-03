/*
 * This file is part of EasyScript.
 *
 * EasyScript is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * EasyScript is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with EasyScript. If not, see <http://www.gnu.org/licenses/>.
 */

#include "message_options.h"
#include "chaiscript/chaiscript.hpp"
#include "easyscript/event_command.h"

EasyScript::MessageOptions::MessageOptions() {
	cmd->SetDefaults(Code::MessageOptions, "", { 0, 0, 0, 0 });
}

EasyScript::MessageOptions EasyScript::MessageOptions::Transparent(int32_t value) {
	cmd->parameters[0] = value;
	return *this;
}

EasyScript::MessageOptions EasyScript::MessageOptions::Position(int32_t value) {
	cmd->parameters[1] = value;
	return *this;
}

EasyScript::MessageOptions EasyScript::MessageOptions::DynamicPosition(int32_t value) {
	cmd->parameters[2] = value;
	return *this;
}

EasyScript::MessageOptions EasyScript::MessageOptions::ContinueEvents(int32_t value) {
	cmd->parameters[3] = value;
	return *this;
}

EasyScript::MessageOptions EasyScript::MessageOptions::Size(int32_t width, int32_t height) {
	if (cmd->parameters.size() <= 7) {
		cmd->parameters.resize(7);
	}
	cmd->parameters[5] = width;
	cmd->parameters[6] = height;
	return *this;
}

EasyScript::MessageOptions EasyScript::MessageOptions::Font(EasyScript::StringArg font, int32_t size) {
	//cmd->SetStringAndMode(4, 2, 7, font);
	if (cmd->parameters.size() <= 9) {
		cmd->parameters.resize(9);
	}
	cmd->parameters[8] = size;
	return *this;
}

void EasyScript::MessageOptions::Register(chaiscript::ChaiScript& chai, EventCommandList& commands) {
	chaiscript::ModulePtr m = std::make_shared<chaiscript::Module>();
	chaiscript::utility::add_class<MessageOptions>(*m, "__cls_MessageOptions",
	{
		chaiscript::constructor<MessageOptions()>()
	},
	{
		{chaiscript::fun(&MessageOptions::Transparent), "__transparent"},
		{chaiscript::fun(&MessageOptions::Position), "__position"},
		{chaiscript::fun(&MessageOptions::DynamicPosition), "avoid_obscuring"},
		{chaiscript::fun(&MessageOptions::ContinueEvents), "continue_events"},
		{chaiscript::fun(&MessageOptions::Size), "size"},
		{chaiscript::fun(&MessageOptions::Font), "font"},
		{chaiscript::fun([&](MessageOptions& obj) {
			return obj.Transparent(0);
		}), "opaque"},
		{chaiscript::fun([&](MessageOptions& obj) {
			return obj.Transparent(1);
		}), "transparent"},
		{chaiscript::fun([&](MessageOptions& obj) {
			return obj.Position(0);
		}), "top"},
		{chaiscript::fun([&](MessageOptions& obj) {
			return obj.Position(1);
		}), "center"},
		{chaiscript::fun([&](MessageOptions& obj) {
			return obj.Position(2);
		}), "bottom"},
	}
	);
	chai.add(m);

	auto o = chai.get_global("@message").get().cast<std::shared_ptr<chaiscript::dispatch::Dynamic_Object>>();
	(*o)["options"] = chaiscript::var(chaiscript::fun([&](){
		auto evt = MessageOptions();
		commands.push_back(evt.cmd);
		return evt;
	}));
	//chai.add_global_const(chaiscript::const_var(0), "$face_left");
	//chai.add_global_const(chaiscript::const_var(1), "$face_right");
}

/*

std::optional<std::string> EasyScript::PlayBgm::StringFromParameter(const Parameter& parameter) {
	auto& fade_in_param = param[0];

	if (&parameter == &fade_in_param) {
		return "";
	}

	return {};
}

*/
