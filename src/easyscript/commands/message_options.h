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

#include "easyscript/forward.h"
#include "easyscript/parameter.h"

namespace EasyScript {

class MessageOptions {
public:
	MessageOptions();

	std::shared_ptr<EventCommand> cmd = std::make_shared<EventCommand>();

	MessageOptions Transparent(int32_t value);
	MessageOptions Position(int32_t value);
	MessageOptions DynamicPosition(int32_t value);
	MessageOptions ContinueEvents(int32_t value);
	MessageOptions Size(int32_t width, int32_t height);
	MessageOptions Font(StringArg font, int32_t size);

	static MessageOptions FromCommand(const EventCommand& command);

	static void Register(State& state);

	static constexpr std::array name = { "MessageOptions", "message", "options" };
};

}
