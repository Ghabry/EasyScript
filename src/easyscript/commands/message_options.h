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

#include <cstdint>

#include "easyscript/commands/command_base.h"
#include "easyscript/forward.h"
#include "easyscript/parameter.h"

namespace EasyScript {

class MessageOptions : public CommandBase<MessageOptions> {
public:
	MessageOptions(State& state) : CommandBase<MessageOptions>(state) {};

	static constexpr std::array name = { "MessageOptions", "message", "options" };
	static constexpr Code code = Code::MessageOptions;

	static constexpr std::array param_default = std::to_array<uint32_t>({0, 0, 0, 0});
	static constexpr std::array param = std::to_array<Parameter>({
		{ "transparent", 0, 0 },
		{ "position", 0, 1 },
		{ "avoid_overlap", 0, 2},
		{ "continue_events", 0, 3},
		{ "w", 0, 5 },
		{ "h", 0, 6 },
		{ "font_size", 0, 8 }
	});
	static constexpr StringParameter string_param = {"font", nullptr, 7, 4, 2};

	static void Register(State& state);
};

}
