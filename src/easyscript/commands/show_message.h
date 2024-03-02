#pragma once

#include <optional>
#include <string>

#include "easyscript/forward.h"

namespace EasyScript {

class ShowMessage {
public:
	ShowMessage(EventCommandList& commands, const std::string& value);
	ShowMessage Line(const std::string& value);

	// Last line belonging to the command
	std::shared_ptr<EventCommand> cmd_end = std::make_shared<EventCommand>();

	static void Register(chaiscript::ChaiScript& chai, EventCommandList& commands);

	static std::optional<std::string> StringFromCommand(EventCommandList& commands);

private:
	EventCommandList& commands;
};

}
