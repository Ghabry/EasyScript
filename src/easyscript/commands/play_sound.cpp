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

#include <format>

EasyScript::PlaySound::PlaySound(StringArg value) {
	cmd->SetDefaults(Code::PlaySound, "", { 100, 100, 50 });
	string_param.Set(*cmd, value);
}

void EasyScript::PlaySound::Register(chaiscript::ChaiScript& chai, EventCommandList& commands) {
	BindAuto<PlaySound, StringArg, PlaySound(StringArg)>(chai, commands);

	BindNamespaceFunctions(
		chai, "sound",
		[&](){
			auto evt = PlaySound(chaiscript::Boxed_Value(std::make_shared<const std::string>("(OFF)")));
			commands.push_back(evt.cmd);
			return evt;
		}, "stop"
	);
}

std::optional<std::string> EasyScript::PlaySound::StringFromCommand(const EventCommand& command) {
	if (string_param.GetMode(command) == 0 && command.string == "(OFF)") {
		return std::format("@{}.stop", name[1]);
	}

	return {};
}
