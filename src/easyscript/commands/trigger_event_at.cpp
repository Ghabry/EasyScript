/*
 * This file is part of EasyScript.
 *
 * EasyScript is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * EasyScript is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with EasyScript. If not, see <http://www.gnu.org/licenses/>.
 */

#include "trigger_event_at.h"
#include "chaiscript/chaiscript.hpp"
#include "easyscript/binding.h"
#include "easyscript/event_command.h"

EasyScript::TriggerEventAt::TriggerEventAt() {
	cmd->SetDefaults(static_cast<Code>(2002), "", { 0, 0, 0, 0 });
}

void EasyScript::TriggerEventAt::Register(State& state) {
	BindAuto<TriggerEventAt, TriggerEventAt()>(state);
}
