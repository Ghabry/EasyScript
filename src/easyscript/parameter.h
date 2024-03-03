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

#include "forward.h"

namespace EasyScript {

struct Parameter {
	const char* name;
	const int32_t default_val = -1;
	const int32_t val_idx = -1;
	const int32_t mode_idx = -1;
	const int32_t mode_shift = -1;

	bool IsDefault(const EventCommand& command) const;
	std::string ToString(const EventCommand& command, bool prefix_name = true) const;
	int32_t GetMode(const EventCommand& command) const;
	int32_t GetValue(const EventCommand& command) const;
	std::array<int32_t, 2> GetValueAndMode(const EventCommand& command) const;
	void Set(EventCommand& command, EasyScript::VariableArg value) const;
	void Set(EventCommand& command, int32_t value) const;
};

struct StringParameter {
	const char* default_val = nullptr;
	const int32_t val_idx = -1;
	const int32_t mode_idx = -1;
	const int32_t mode_shift = -1;

	bool IsDefault(const EventCommand& command) const;
	std::string ToString(const EventCommand& command) const;
	int32_t GetMode(const EventCommand& command) const;
	void Set(EventCommand& command, EasyScript::StringArg value) const;
	void Set(EventCommand& command, const std::string& value) const;
};

}
