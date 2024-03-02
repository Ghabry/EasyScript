#pragma once

#include "easyscript/forward.h"
#include "easyscript/parameter.h"

#include <optional>

namespace EasyScript {

class PlaySound {
public:
	PlaySound(StringArg value);

	std::shared_ptr<EventCommand> cmd = std::make_shared<EventCommand>();

	static void Register(chaiscript::ChaiScript& chai, EventCommandList& commands);

	static constexpr std::array name = { "PlaySound", "sound", "play" };

	static constexpr const std::array param = std::to_array<Parameter>({
		{ "volume", 100, 0, 3, 1 },
		{ "tempo", 100, 1, 3, 2 },
		{ "balance", 50, 2, 3, 3 }
	});
	static constexpr const StringParameter string_param = {nullptr, 4, 3, 0};

	static std::optional<std::string> StringFromCommand(const EventCommand& command);
};

}
