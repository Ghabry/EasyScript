#pragma once

#include "easyscript/forward.h"
#include "easyscript/parameter.h"

namespace EasyScript {

class CallCommonEvent {
public:
	CallCommonEvent(VariableArg value);

	std::shared_ptr<EventCommand> cmd = std::make_shared<EventCommand>();

	static void Register(chaiscript::ChaiScript& chai, EventCommandList& commands);

	static constexpr std::array name = { "CallCommonEvent", "battle", "ce" };

	static constexpr const Parameter constructor_param = {"event", 1, 0, 1};
};

}
