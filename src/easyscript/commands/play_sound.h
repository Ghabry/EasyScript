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

class PlaySound : public CommandBase<PlaySound> {
public:
	PlaySound(State& state, StringArg value) : CommandBase<PlaySound>(state, value) {};

	static void Register(State& state);

	static constexpr std::array name = { "PlaySound", "sound", "play" };
	static constexpr Code code = Code::PlaySound;

	static constexpr std::array param_default = std::to_array<uint32_t>({ 100, 100, 50 });
	static constexpr std::array param = std::to_array<Parameter>({
		{ "volume", 100, 0, 3, 1 },
		{ "tempo", 100, 1, 3, 2 },
		{ "balance", 50, 2, 3, 3 }
	});
	static constexpr StringParameter constructor_param = {nullptr, 4, 3, 0};

	static std::optional<std::string> StringFromCommand(const EventCommand& command);
};

}
