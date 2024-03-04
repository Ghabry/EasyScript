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

class ShowChoiceOption {
public:
	ShowChoiceOption(EasyScript::State& state, const std::string& label, bool is_cancel) : is_cancel(is_cancel) {
		cmd = std::make_shared<EasyScript::EventCommand>(EasyScript::Code::ShowChoiceOption, state.indent);
		cmd->string = label;

		auto& commands = state.commands;
		commands.push_back(cmd);

		for (auto it = commands.rbegin() + 1; it != commands.rend(); ++it) {
			if ((*it)->indent == state.indent) {
				if ((*it)->code == EasyScript::Code::ShowChoiceOption) {
					if ((*it)->parameters[0] == 5) {
						throw std::runtime_error("Cancel case must be last");
					}
					++child_num;
					continue;
				} else if ((*it)->code == EasyScript::Code::ShowChoice) {
					parent = it->get();
					break;
				} else {
					throw std::runtime_error("Invalid command");
				}
			}
		}

		if (parent == nullptr) {
			throw std::runtime_error("ShowChoiceOption has no parent");
		}

		if (is_cancel) {
			cmd->parameters = {4};
			parent->parameters = {5};
		} else {
			cmd->parameters = { child_num };
		}

		state.indent++;
	}

	ShowChoiceOption Cancel() {
		if (is_cancel) {
			throw std::runtime_error("Do not call cancel on @cancel");
		}

		parent->parameters = { child_num + 1 };
		return *this;
	}

	std::shared_ptr<EasyScript::EventCommand> cmd;

private:
	int child_num = 0;
	bool is_cancel;
	EasyScript::EventCommand* parent = nullptr;
};

EasyScript::ShowChoice::ShowChoice(EasyScript::State& state) {
	cmd->SetDefaults(Code::ShowChoice, "", { 0 });

	auto& chai = state.chai;

	chai.add(chaiscript::fun([&state]() {
		auto end_command = std::make_shared<EventCommand>();
		end_command->code = Code::ShowChoiceEnd;
		end_command->indent = state.indent;
		state.commands.push_back(end_command);
	}), "#block_end");

	state.commands.push_back(cmd);
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
	/*BindConstructors<ShowChoice, ShowChoice(State&)>(
		chai, "ShowChoice");*/

	chai.add(chaiscript::fun([&state, &chai](const std::string& label) {
		chai.add(chaiscript::fun([&state]() {
			auto end_command = std::make_shared<EventCommand>();
			end_command->code = Code::END;
			end_command->indent = state.indent;
			state.commands.push_back(end_command);
			state.indent--;
		}), "#block_end");

		return ShowChoiceOption(state, label, false);
	}), "@case");

	chai.add(chaiscript::fun([&state, &chai]() {
		chai.add(chaiscript::fun([&state]() {
			auto end_command = std::make_shared<EventCommand>();
			end_command->code = Code::END;
			end_command->indent = state.indent;
			state.commands.push_back(end_command);
			state.indent--;
		}), "#block_end");

		return ShowChoiceOption(state, {}, true);
	}), "@cancel");

	BindFunctions<ShowChoiceOption>(chai,
		&ShowChoiceOption::Cancel, "cancel"
	);
}

std::optional<std::string> EasyScript::ShowChoice::StringFromCommand(const EventCommand& command) {
	return {};
}
