#include "play_bgm.h"
#include "chaiscript/chaiscript.hpp"
#include "easyscript/binding.h"
#include "easyscript/event_command.h"
#include "easyscript/forward.h"

#include <format>
#include <optional>

EasyScript::PlayBgm::PlayBgm(StringArg value) {
	cmd->SetDefaults(Code::PlayBGM, "", { 0, 100, 100, 50 });
	string_param.Set(*cmd, value);
}

void EasyScript::PlayBgm::Register(chaiscript::ChaiScript& chai, EventCommandList& commands) {
	BindAuto<PlayBgm, StringArg, PlayBgm(StringArg)>(chai, commands);

	BindNamespaceFunctions(
		chai, "music",
		[&](){
			auto evt = PlayBgm(chaiscript::Boxed_Value(std::make_shared<const std::string>("(OFF)")));
			commands.push_back(evt.cmd);
			return evt;
		}, "stop"
	);
}

std::optional<std::string> EasyScript::PlayBgm::StringFromCommand(const EventCommand& command) {
	if (string_param.GetMode(command) == 0 && command.string == "(OFF)") {
		return "@music.stop";
	}

	return {};
}
