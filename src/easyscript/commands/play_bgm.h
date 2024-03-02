#pragma once

#include "easyscript/forward.h"
#include "easyscript/parameter.h"

#include <optional>

namespace EasyScript {

class PlayBgm {
public:
	PlayBgm(StringArg value);

	std::shared_ptr<EventCommand> cmd = std::make_shared<EventCommand>();

	static void Register(chaiscript::ChaiScript& chai, EventCommandList& commands);

	static constexpr std::array name = { "PlayBgm", "music", "play" };

	static constexpr const std::array param = std::to_array<Parameter>({
		{ "fadein", 0, 0, 4, 1 },
		{ "volume", 100, 1, 4, 2 },
		{ "tempo", 100, 2, 4, 3 },
		{ "balance", 50, 3, 4, 4 }
	});
	static constexpr const StringParameter string_param = {nullptr, 5, 4, 0};

	static std::optional<std::string> StringFromCommand(const EventCommand& command);
};

}
