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

#include "play_bgm.h"
#include "chaiscript/chaiscript.hpp"
#include "easyscript/binding.h"
#include "easyscript/event_command.h"
#include "easyscript/state.h"

#include <format>
#include <optional>

void EasyScript::PlayBgm::Register(State& state) {
	Bind<PlayBgm, PlayBgm(State&, StringArg)>(state);

	auto& chai = state.chai;

	BindNamespaceFunctions(
		chai, "music",
		[&](){
			auto evt = PlayBgm(state, chaiscript::Boxed_Value(std::make_shared<const std::string>("(OFF)")));
			state.commands.push_back(evt.cmd);
			return evt;
		}, "stop"
	);
}

std::optional<std::string> EasyScript::PlayBgm::StringFromCommand(const EventCommand& command) {
	if (constructor_param.GetMode(command) == 0 && command.string == "(OFF)") {
		return "@music.stop";
	}

	return {};
}
