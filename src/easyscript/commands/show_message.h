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

#include <optional>
#include <string>

#include "easyscript/forward.h"

namespace EasyScript {

class ShowMessage {
public:
	ShowMessage(State& state, const std::string& value);
	ShowMessage Line(const std::string& value);

	// Last line belonging to the command
	std::shared_ptr<EventCommand> cmd_end = std::make_shared<EventCommand>();

	static void Register(State& state);

	static std::optional<std::string> StringFromCommand(EventCommandList& commands);

private:
	EventCommandList& commands;
};

}
