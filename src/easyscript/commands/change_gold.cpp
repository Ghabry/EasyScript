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

#include "change_gold.h"
#include "chaiscript/chaiscript.hpp"
#include "easyscript/binding.h"
#include "easyscript/event_command.h"
#include "easyscript/forward.h"
#include "easyscript/state.h"
#include <format>

static constexpr const EasyScript::Parameter op_param = { "op", 0, 0 };
static constexpr const EasyScript::Parameter op_num = { "num", 0, 2, 1 };


void EasyScript::ChangeGold::Register(State& state) {
	Bind<ChangeGold, ChangeGold(State&)>(state,
		&ChangeGold::Add, "add",
		&ChangeGold::Sub, "sub",
		&ChangeGold::Add, "+=",
		&ChangeGold::Sub, "-=");
}

EasyScript::ChangeGold EasyScript::ChangeGold::Add(EasyScript::VariableArg value) {
	op_param.Set(*cmd, 0);
	op_num.Set(*cmd, value);
	return *this;
}

EasyScript::ChangeGold EasyScript::ChangeGold::Sub(VariableArg value) {
	op_param.Set(*cmd, 1);
	op_num.Set(*cmd, value);
	return *this;
}

std::optional<std::string> EasyScript::ChangeGold::StringFromCommand(const EventCommand& command) {
	std::string line = std::format("@{}.{}", ChangeGold::name[1], ChangeGold::name[2]);

	line += (op_param.GetValue(command) == 0 ? " += " : " -= ");
	line += op_num.ToString(command, false);

	return line;
}
