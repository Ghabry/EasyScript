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

#include "play_sound.h"
#include "chaiscript/chaiscript.hpp"
#include "easyscript/binding.h"
#include "easyscript/event_command.h"
#include "easyscript/state.h"

#include <format>

void EasyScript::PlaySound::Register(State& state) {
	Bind<PlaySound, PlaySound(State&, StringArg)>(state);

	auto& chai = state.chai;

	BindNamespaceFunctions(
		chai, "sound",
		[&](){
			auto evt = PlaySound(state, chaiscript::Boxed_Value(std::make_shared<const std::string>("(OFF)")));
			state.commands.push_back(evt.cmd);
			return evt;
		}, "stop"
	);
}

std::optional<std::string> EasyScript::PlaySound::StringFromCommand(const EventCommand& command) {
	if (constructor_param.GetMode(command) == 0 && command.string == "(OFF)") {
		return std::format("@{}.stop", name[1]);
	}

	return {};
}
