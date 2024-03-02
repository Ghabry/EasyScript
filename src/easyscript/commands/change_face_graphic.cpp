#include "change_face_graphic.h"
#include "chaiscript/chaiscript.hpp"
#include "easyscript/binding.h"
#include "easyscript/event_command.h"

EasyScript::ChangeFaceGraphic::ChangeFaceGraphic(EasyScript::StringArg value) {
	cmd->SetDefaults(Code::ChangeFaceGraphic, "", { 1, 0, 0, 0 });
	string_param.Set(*cmd, value);
}

void EasyScript::ChangeFaceGraphic::Register(chaiscript::ChaiScript& chai, EventCommandList& commands) {
	BindAuto<ChangeFaceGraphic, StringArg, ChangeFaceGraphic(StringArg)>(chai, commands);

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
