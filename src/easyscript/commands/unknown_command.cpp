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

#include "unknown_command.h"
#include "chaiscript/chaiscript.hpp"
#include "easyscript/binding.h"
#include "easyscript/event_command.h"
#include "easyscript/state.h"
#include <format>

EasyScript::UnknownCommand::UnknownCommand(State& state, int32_t value)
	: CommandBase<UnknownCommand>(state) {
	cmd->code = static_cast<Code>(value);
}

EasyScript::UnknownCommand EasyScript::UnknownCommand::String(std::string string) {
	cmd->string = string;
	return *this;
}

EasyScript::UnknownCommand EasyScript::UnknownCommand::Parameter(std::vector<int32_t> parameters) {
	cmd->parameters = parameters;
	return *this;
}

void EasyScript::UnknownCommand::Register(State& state) {
	Bind<UnknownCommand, UnknownCommand(State&, int32_t)>(state,
		&UnknownCommand::String, "string",
		&UnknownCommand::Parameter, "args");
}

std::optional<std::string> EasyScript::UnknownCommand::StringFromCommand(const EventCommand& command) {
	std::string line = std::format("@command({})", static_cast<int>(command.code));

	if (!command.string.empty()) {
		line += std::format(".string(\"{}\")", command.GetEscapedString());
	}

	if (!command.parameters.empty()) {
		line += ".args([";
		for (auto& parameter: command.parameters) {
			line += std::to_string(parameter) + ",";
		}
		line.pop_back();
		line += "])";
	}

	return line;
}
