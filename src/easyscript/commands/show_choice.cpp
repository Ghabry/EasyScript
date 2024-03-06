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
#include <format>
#include <stdexcept>

EasyScript::ShowChoice::ShowChoice(EasyScript::State& state, const std::string& label) : CommandBase<ShowChoice>(state) {
	state.commands.push_back(cmd);

	ShowChoiceOption(state, label, false);
}

EasyScript::ShowChoice EasyScript::ShowChoice::Cancel() {
	cmd->parameters = {1};
	return *this;
}

void EasyScript::ShowChoice::Register(State& state) {
	Bind<ShowChoice, ShowChoice(State&, const std::string& label)>(state);

	BindFunctions<ShowChoice>(state.chai,
		&ShowChoice::Cancel, "cancel"
	);
}

std::optional<std::string> EasyScript::ShowChoice::StringFromCommand(const EventCommandList& commands, size_t index) {
	assert(commands[index+1]->code == Code::ShowChoiceOption);

	std::string line = std::format("@message.choice(\"{}\")", commands[index+1]->string);
	if (!commands[index]->parameters.empty() && commands[index]->parameters[0] == 1) {
		line += ".cancel";
	}

	line += " {";

	return line;
}

EasyScript::ShowChoiceOption::ShowChoiceOption(EasyScript::State& state, const std::string& label, bool is_cancel) :
		EasyScript::CommandBase<ShowChoiceOption>(state), is_cancel(is_cancel) {
	cmd->string = label;

	auto& commands = state.commands;
	commands.push_back(cmd);

	for (auto it = commands.rbegin() + 1; it != commands.rend(); ++it) {
		if ((*it)->indent == state.indent) {
			if ((*it)->code == EasyScript::Code::ShowChoiceOption) {
				if ((*it)->parameters[0] == 5) {
					throw std::runtime_error("ShowChoiceOption: Cancel case must be last");
				}
				++child_num;
				continue;
			} else if ((*it)->code == EasyScript::Code::ShowChoice) {
				parent = it->get();
				break;
			} else {
				throw std::runtime_error(std::format("ShowChoiceOption: Invalid command {}", static_cast<int>((*it)->code)));
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

	state.chai.add(chaiscript::fun([&state]() {
		auto end_command = std::make_shared<EventCommand>();
		end_command->code = Code::END;
		end_command->indent = state.indent;
		state.commands.push_back(end_command);
		state.indent--;
	}), "#block_end");

}

EasyScript::ShowChoiceOption EasyScript::ShowChoiceOption::Cancel() {
	if (is_cancel) {
		throw std::runtime_error("Do not call cancel on @cancel");
	}

	parent->parameters = { child_num + 1 };
	return *this;
}

void EasyScript::ShowChoiceOption::Register(State& state) {
	auto& chai = state.chai;

	// Case block
	chai.add(chaiscript::fun([&state, &chai](const std::string& label) {
		return ShowChoiceOption(state, label, false);
	}), "@case");

	// Cancel option
	chai.add(chaiscript::fun([&state, &chai]() {
		return ShowChoiceOption(state, {}, true);
	}), "@cancel");

	BindFunctions<ShowChoiceOption>(chai,
		&ShowChoiceOption::Cancel, "cancel"
	);
}

std::optional<std::string> EasyScript::ShowChoiceOption::StringFromCommand(const EventCommandList& commands, size_t index, const EventCommand& parent) {
	std::string line;
	auto& this_cmd = *commands[index];
	int child_count = 0;
	int cancel = parent.parameters[0];

	for (auto it = std::make_reverse_iterator(commands.begin() + index); it != commands.rend(); ++it) {
		auto& cmd = **it;
		if (cmd.indent == this_cmd.indent) {
			if (cmd.code == Code::ShowChoice && &cmd == &parent) {
				break;
			} else if (cmd.code == Code::ShowChoiceOption) {
				++child_count;
			} else {
				throw chaiscript::exception::eval_error(std::format("ShowChoiceOption::StringFromCommand: Unexpected event command {}", static_cast<int>(cmd.code)));
			}
		}
	}

	line += "} ";

	if (this_cmd.parameters[0] == 4) {
		line += "@cancel";
	} else {
		line += std::format("@case(\"{}\")", this_cmd.string);
		if (cancel == child_count + 1) {
			line += ".cancel";
		}
	}

	line += " {";

	return line;
}
