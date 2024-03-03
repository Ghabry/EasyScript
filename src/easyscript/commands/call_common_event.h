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

#include "easyscript/forward.h"
#include "easyscript/parameter.h"

namespace EasyScript {

class CallCommonEvent {
public:
	CallCommonEvent(VariableArg value);

	std::shared_ptr<EventCommand> cmd = std::make_shared<EventCommand>();

	static void Register(State& state);

	static constexpr std::array name = { "CallCommonEvent", "battle", "ce" };

	static constexpr const Parameter constructor_param = {"event", 1, 0, 1};
};

}
