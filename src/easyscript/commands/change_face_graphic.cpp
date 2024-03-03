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

#include "change_face_graphic.h"
#include "chaiscript/chaiscript.hpp"
#include "easyscript/binding.h"
#include "easyscript/event_command.h"

EasyScript::ChangeFaceGraphic::ChangeFaceGraphic(EasyScript::StringArg value) {
	cmd->SetDefaults(Code::ChangeFaceGraphic, "", { 1, 0, 0, 0 });
	string_param.Set(*cmd, value);
}

void EasyScript::ChangeFaceGraphic::Register(chaiscript::ChaiScript& chai, State& state) {
	BindAuto<ChangeFaceGraphic, ChangeFaceGraphic(StringArg)>(chai, state);

	BindFunctions<ChangeFaceGraphic>(
		chai,
		[&](ChangeFaceGraphic& obj) {
			position_param.Set(*obj.cmd, 0);
		}, "left",
		[&](ChangeFaceGraphic& obj) {
			position_param.Set(*obj.cmd, 1);
		}, "right"
	);

	chai.add_global_const(chaiscript::const_var(0), "$face_left");
	chai.add_global_const(chaiscript::const_var(1), "$face_right");
}

std::optional<std::string> EasyScript::ChangeFaceGraphic::StringFromParameter(const EventCommand& command, const Parameter& parameter) {
	if (&parameter == &position_param) {
		auto [value, mode] = position_param.GetValueAndMode(command);
		if (mode == 0 && value == 0) {
			return ".left";
		} else if (mode == 0 && value == 1) {
			return ".right";
		}
	}

	return {};
}
