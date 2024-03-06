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

#include "easyscript/event_command.h"
#include "easyscript/forward.h"

namespace EasyScript {

template<typename T>
class CommandBase {
public:
	CommandBase(EasyScript::State& state) {
		cmd->code = T::code;
		// Ugly hack to prevent heavy include of chaiscript.h
		cmd->indent = reinterpret_cast<PartialState&>(state).indent;

		if constexpr (requires { T::string_param; } ) {
			if (T::string_param.default_val != nullptr) {
				cmd->string = T::string_param.default_val;
			}
		}

		if constexpr (requires { T::param_default; } ) {
			cmd->parameters = {T::param_default.begin(), T::param_default.end() };
		}
	}

	CommandBase(EasyScript::State& state, auto& value)
			requires requires { static_cast<T*>(this)->constructor_param; } : CommandBase(state) {
		static_cast<T*>(this)->constructor_param.Set(*cmd, value);
	}

	std::shared_ptr<EventCommand> cmd = std::make_shared<EventCommand>();

private:
	struct PartialState {
		int indent = 0;
		EventCommandList commands;
	};

};

}
