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

#include <string>
#include <string_view>
#include <vector>
#include <cstdint>

#include "forward.h"

namespace EasyScript {

class EventCommand {
public:
	EventCommand() = default;

	void SetDefaults(Code code, std::string_view string, std::initializer_list<int32_t> parameters);

	std::string GetEscapedString() const;

	static void RegisterAll(chaiscript::ChaiScript& chai, State& state);

	Code code = static_cast<Code>(0);
	int32_t indent = 0;
	std::string string;
	std::vector<int32_t> parameters;
};

}
