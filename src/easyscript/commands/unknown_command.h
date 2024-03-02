#pragma once

#include "easyscript/forward.h"
#include "easyscript/parameter.h"
#include <optional>

namespace EasyScript {

class UnknownCommand {
public:
	UnknownCommand(int32_t value);

	UnknownCommand String(std::string string);
	UnknownCommand Parameter(std::vector<int32_t> parameters);

	std::shared_ptr<EventCommand> cmd = std::make_shared<EventCommand>();

	static void Register(chaiscript::ChaiScript& chai, EventCommandList& commands);

	static std::optional<std::string> StringFromCommand(const EventCommand& command);
};

}
