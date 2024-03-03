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

#include <optional>

namespace EasyScript {

class PlaySound {
public:
	PlaySound(StringArg value);

	std::shared_ptr<EventCommand> cmd = std::make_shared<EventCommand>();

	static void Register(State& state);

	static constexpr std::array name = { "PlaySound", "sound", "play" };

	static constexpr const std::array param = std::to_array<Parameter>({
		{ "volume", 100, 0, 3, 1 },
		{ "tempo", 100, 1, 3, 2 },
		{ "balance", 50, 2, 3, 3 }
	});
	static constexpr const StringParameter string_param = {nullptr, 4, 3, 0};

	static std::optional<std::string> StringFromCommand(const EventCommand& command);
};

}
