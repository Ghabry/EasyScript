#pragma once

#include "easyscript/forward.h"
#include "easyscript/parameter.h"

namespace EasyScript {

class TriggerEventAt {
public:
	TriggerEventAt();

	std::shared_ptr<EventCommand> cmd = std::make_shared<EventCommand>();

	static void Register(chaiscript::ChaiScript& chai, EventCommandList& commands);

	static constexpr std::array name = { "TriggerEventAt", "map", "trigger" };
	static constexpr Code code = static_cast<Code>(2002);
	static constexpr std::array param_default = std::to_array<uint32_t>({0, 0, 0, 0});
	static constexpr const std::array param = std::to_array<Parameter>({
		{ "x", 0, 1, 0 },
		{ "y", 0, 3, 2 },
	});
};

}
