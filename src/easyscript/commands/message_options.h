#pragma once

#include <cstdint>

#include "easyscript/forward.h"
#include "easyscript/parameter.h"

namespace EasyScript {

class MessageOptions {
public:
	MessageOptions();

	std::shared_ptr<EventCommand> cmd = std::make_shared<EventCommand>();

	MessageOptions Transparent(int32_t value);
	MessageOptions Position(int32_t value);
	MessageOptions DynamicPosition(int32_t value);
	MessageOptions ContinueEvents(int32_t value);
	MessageOptions Size(int32_t width, int32_t height);
	MessageOptions Font(StringArg font, int32_t size);

	static MessageOptions FromCommand(const EventCommand& command);

	static void Register(chaiscript::ChaiScript& chai, EventCommandList& commands);

	static constexpr std::array name = { "MessageOptions", "message", "options" };
};

}
