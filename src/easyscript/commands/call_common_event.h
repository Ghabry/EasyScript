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

namespace EasyScript {

class CallCommonEvent : public CommandBase<CallCommonEvent> {
public:
	CallCommonEvent(State& state, VariableArg value) : CommandBase<CallCommonEvent>(state, value) {};

	static constexpr std::array name = { "CallCommonEvent", "battle", "ce" };
	static constexpr Code code = Code::CallCommonEvent;

	static constexpr std::array param_default = std::to_array<uint32_t>({0});
	static constexpr const Parameter constructor_param = {"event", 1, 0, 1};
};

}
