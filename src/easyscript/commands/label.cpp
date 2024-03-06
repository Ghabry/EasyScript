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

#include "label.h"
#include "chaiscript/chaiscript.hpp"
#include "easyscript/binding.h"
#include "easyscript/event_command.h"
#include "easyscript/state.h"
#include <format>

void EasyScript::Label::Register(State& state) {
	Bind<Label, Label(State&, VariableArg)>(state,
		&Label::Goto, "goto");
}

EasyScript::Label EasyScript::Label::Goto() {
	cmd->code = Code::JumpToLabel;

	return *this;
}

std::optional<std::string> EasyScript::Label::StringFromCommand(const EventCommand& command) {
	std::string line = std::format("@{}", name[1]);
	line += constructor_param.ToString(command);

	if (command.code == Code::JumpToLabel) {
		line += ".goto";
	}

	return line;
}
