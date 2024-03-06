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
#include "command_base.h"

namespace EasyScript {

class TriggerEventAt : public CommandBase<TriggerEventAt> {
public:
	TriggerEventAt(State& state) : CommandBase<TriggerEventAt>(state) {};

	static constexpr std::array name = { "TriggerEventAt", "map", "trigger" };
	static constexpr Code code = static_cast<Code>(2002);

	static constexpr std::array param_default = std::to_array<uint32_t>({0, 0, 0, 0});
	static constexpr std::array param = std::to_array<Parameter>({
		{ "x", 0, 1, 0 },
		{ "y", 0, 3, 2 },
	});
};

}
