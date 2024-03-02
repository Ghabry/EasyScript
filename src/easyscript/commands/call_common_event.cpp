#include "call_common_event.h"
#include "chaiscript/chaiscript.hpp"
#include "easyscript/binding.h"
#include "easyscript/event_command.h"

EasyScript::CallCommonEvent::CallCommonEvent(VariableArg value) {
	cmd->SetDefaults(Code::CallCommonEvent, "", { 0 });
	constructor_param.Set(*cmd, value);
}

void EasyScript::CallCommonEvent::Register(chaiscript::ChaiScript& chai, EventCommandList& commands) {
	BindAuto<CallCommonEvent, VariableArg, CallCommonEvent(VariableArg)>(
		chai, commands
	);
}
