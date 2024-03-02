#include "trigger_event_at.h"
#include "chaiscript/chaiscript.hpp"
#include "easyscript/binding.h"
#include "easyscript/event_command.h"

EasyScript::TriggerEventAt::TriggerEventAt() {
	cmd->SetDefaults(static_cast<Code>(2002), "", { 0, 0, 0, 0 });
}

void EasyScript::TriggerEventAt::Register(chaiscript::ChaiScript& chai, EventCommandList& commands) {
	BindAuto<TriggerEventAt, void, TriggerEventAt()>(chai, commands);
}
