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

#pragma once

#include "easyscript/commands/command_base.h"
#include "easyscript/forward.h"
#include "easyscript/parameter.h"
#include <optional>

namespace EasyScript {

class UnknownBranchCommand : public CommandBase<UnknownBranchCommand> {
public:
	UnknownBranchCommand(State& state, int32_t value);

	UnknownBranchCommand String(std::string string);
	UnknownBranchCommand Parameter(std::vector<int32_t> parameters);

	static constexpr std::array name = { "UnknownBranchCommand", "branch" };
	static constexpr Code code = static_cast<Code>(-1);

	static void Register(State& state);

	static std::optional<std::string> StringFromCommand(const EventCommandList& commands, size_t index, const EventCommand& parent);

	Code code_end;
};

class UnknownElseCommand : public CommandBase<UnknownElseCommand> {
public:
	UnknownElseCommand(State& state, int32_t value);

	UnknownElseCommand String(std::string string);
	UnknownElseCommand Parameter(std::vector<int32_t> parameters);

	static constexpr std::array name = { "UnknownElseCommand" };
	static constexpr Code code = static_cast<Code>(-1);

	static void Register(State& state);

	static std::optional<std::string> StringFromCommand(const EventCommandList& commands, size_t index, const EventCommand& parent);

private:
	int child_num = 0;
	EasyScript::EventCommand* parent = nullptr;
};

}
