#pragma once

#include <memory>
#include <lcf/rpg/eventcommand.h>

namespace chaiscript {
	class Boxed_Value;
	class ChaiScript;
}

namespace EasyScript {
	class EventCommand;
	using Code = lcf::rpg::EventCommand::Code;
	using EventCommandList = std::vector<std::shared_ptr<EventCommand>>;
	using VariableArg = const chaiscript::Boxed_Value&;
	using StringArg = const chaiscript::Boxed_Value&;
}
