#pragma once

#include "easyscript/forward.h"
#include "easyscript/parameter.h"

#include <optional>

namespace EasyScript {

class ChangeFaceGraphic {
public:
	ChangeFaceGraphic(StringArg value);

	std::shared_ptr<EventCommand> cmd = std::make_shared<EventCommand>();

	static void Register(chaiscript::ChaiScript& chai, EventCommandList& commands);

	static constexpr std::array name = { "ChangeFaceGraphic", "message", "face" };

	static constexpr const std::array param = std::to_array<Parameter>({
		{ "index", 1, 0, 3, 1 },
		{ "position", 0, 1 },
		{ "flip", 0, 2 }
	});
	static constexpr const StringParameter string_param = {nullptr, 4, 3, 0};

	static constexpr const Parameter& position_param = param[1];

	static std::optional<std::string> StringFromParameter(const EventCommand& command, const Parameter& parameter);
};

}
