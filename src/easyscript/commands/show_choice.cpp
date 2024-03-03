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

#include "show_choice.h"
#include "chaiscript/chaiscript.hpp"
#include "easyscript/binding.h"
#include "easyscript/event_command.h"

EasyScript::ShowChoice::ShowChoice(EasyScript::State& state) {
	cmd->SetDefaults(Code::ShowChoice, "", { 1, 0, 0, 0 });

	auto& chai = state.chai;
/*
	chai.add(chaiscript::fun([&](int a) {
		chai.add(chaiscript::fun([=]() {
			state.indent--;
		}), "#block_end");
	}), "@if");*/

	state.indent++;
}

void EasyScript::ShowChoice::Register(State& state) {
	BindAuto<ShowChoice, ShowChoice(State&)>(state);
}

std::optional<std::string> EasyScript::ShowChoice::StringFromCommand(const EventCommand& command) {

}
