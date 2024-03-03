#include "show_message.h"
#include "chaiscript/chaiscript.hpp"
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

#include "easyscript/binding.h"
#include "easyscript/event_command.h"
#include "easyscript/forward.h"
#include "easyscript/state.h"
#include "easyscript/utils.h"
#include <format>
#include <sstream>

EasyScript::ShowMessage::ShowMessage(EasyScript::State& state, const std::string& value) :
	commands(state.commands) {

	std::istringstream ss(std::string{value});
	std::string line;

	bool first = true;

	while (Utils::ReadLine(ss, line)) {
		auto cmd = std::make_shared<EventCommand>();
		if (first) {
			cmd->SetDefaults(Code::ShowMessage, line, {});
			first = false;
		} else {
			cmd->SetDefaults(Code::ShowMessage_2, line, {});
		}
		commands.push_back(cmd);
	}

	if (commands.empty()) {
		auto cmd = std::make_shared<EventCommand>();
		cmd->SetDefaults(Code::ShowMessage, "", {});
		commands.push_back(cmd);
	}

	cmd_end = commands.back();
}

EasyScript::ShowMessage EasyScript::ShowMessage::Line(const std::string& value) {
	auto cmd = std::make_shared<EventCommand>();
	cmd->SetDefaults(Code::ShowMessage_2, value, {});

	auto it = std::find(commands.begin(), commands.end(), cmd_end);
	commands.insert(std::next(it), cmd);
	cmd_end = cmd;

	return *this;
}

void EasyScript::ShowMessage::Register(chaiscript::ChaiScript& chai, State& state) {
	BindConstructors<ShowMessage, ShowMessage(State&, const std::string&)>(
		chai, "ShowMessage");

	BindFunctions<ShowMessage>(chai,
		&ShowMessage::Line, "line",
		[](ShowMessage& obj) {
			return obj.Line("");
		}, "newline"
	);

	BindNamespaceFunctions(
		chai, "message",
		[&](const std::string& value){
			auto evt = ShowMessage(state, value);
			return evt;
		}, "show"
	);
}

std::optional<std::string> EasyScript::ShowMessage::StringFromCommand(EasyScript::EventCommandList& commands) {
	assert(!commands.empty());

	std::string line = std::format("@message.show(\"{}\")", commands[0]->GetEscapedString());

	for (auto& command: std::span(commands).subspan(1)) {
		if (command->string.empty()) {
			line += "\n  .newline";
		} else {
			line += std::format("\n  .line(\"{}\")", command->GetEscapedString());
		}
	}

	return line;
}
