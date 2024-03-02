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
