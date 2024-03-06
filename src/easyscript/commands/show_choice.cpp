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
#include <memory>
#include <stdexcept>

EasyScript::ShowChoice::ShowChoice(EasyScript::State& state) : CommandBase<ShowChoice>(state) {
	state.chai.add(chaiscript::fun([&state]() {
		auto end_command = std::make_shared<EventCommand>();
		end_command->code = Code::ShowChoiceEnd;
		end_command->indent = state.indent;
		state.commands.push_back(end_command);
	}), "#block_end");
}

void EasyScript::ShowChoice::Register(State& state) {
	auto& chai = state.chai;

	BindConstructors<ShowChoice, ShowChoice(State&)>(
		chai, "ShowChoice");

	BindNamespaceFunctions(
		chai, "message",
		[&state](){
			auto evt = ShowChoice(state);
			return evt;
		}, "choice"
	);
}
