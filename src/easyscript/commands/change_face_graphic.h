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

class ChangeFaceGraphic {
public:
	ChangeFaceGraphic(StringArg value);

	std::shared_ptr<EventCommand> cmd = std::make_shared<EventCommand>();

	static void Register(chaiscript::ChaiScript& chai, EventCommandList& commands);

	static constexpr std::array name = { "ChangeFaceGraphic", "message", "face" };

	static constexpr const std::array param = std::to_array<Parameter>({
		{ "index", 1, 0, 3, 1 },
		{ "position", 0, 1 },
		{ "flip", 0, 2 }
	});
	static constexpr const StringParameter string_param = {nullptr, 4, 3, 0};

	static constexpr const Parameter& position_param = param[1];

	static std::optional<std::string> StringFromParameter(const EventCommand& command, const Parameter& parameter);
};

}
