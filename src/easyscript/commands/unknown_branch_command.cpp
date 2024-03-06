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

#include "unknown_branch_command.h"
#include "chaiscript/chaiscript.hpp"
#include "easyscript/binding.h"
#include "easyscript/event_command.h"
#include "easyscript/state.h"
#include <cstdint>
#include <format>

EasyScript::UnknownBranchCommand::UnknownBranchCommand(State& state, int32_t value)
	: CommandBase<UnknownBranchCommand>(state) {
	cmd->code = static_cast<Code>(value);

	// Not really "Unknown", the list of end commands is hardcoded here
	if (cmd->code == Code::ConditionalBranch) {
		code_end = Code::EndBranch;
	} else if (cmd->code == Code::ConditionalBranch_B) {
		code_end = Code::EndBranch_B;
	} else if (cmd->code == Code::Loop) {
		code_end = Code::EndLoop;
	} else if (cmd->code == Code::EnemyEncounter) {
		code_end = Code::EndBattle;
	} else if (cmd->code == Code::OpenShop) {
		code_end = Code::EndShop;
	} else if (cmd->code == Code::Stay) {
		code_end = Code::EndInn;
	} else {
		assert(false);
	}

	state.chai.add(chaiscript::fun([&state, this]() {
		auto end_command = std::make_shared<EventCommand>();
		end_command->code = code_end;
		end_command->indent = state.indent;
		state.commands.push_back(end_command);
	}), "#block_end");

	state.indent++;
}

EasyScript::UnknownBranchCommand EasyScript::UnknownBranchCommand::String(std::string string) {
	cmd->string = string;
	return *this;
}

EasyScript::UnknownBranchCommand EasyScript::UnknownBranchCommand::Parameter(std::vector<int32_t> parameters) {
	cmd->parameters = parameters;
	return *this;
}

void EasyScript::UnknownBranchCommand::Register(State& state) {
	Bind<UnknownBranchCommand, UnknownBranchCommand(State&, int32_t)>(state,
		&UnknownBranchCommand::String, "string",
		&UnknownBranchCommand::Parameter, "args");
}

std::optional<std::string> EasyScript::UnknownBranchCommand::StringFromCommand(const EventCommand& command) {
	std::string line = std::format("@branch({})", static_cast<int>(command.code));

	if (!command.string.empty()) {
		line += std::format(".string(\"{}\")", command.GetEscapedString());
	}

	if (!command.parameters.empty()) {
		line += ".args([";
		for (auto& parameter: command.parameters) {
			line += std::to_string(parameter) + ",";
		}
		line.pop_back();
		line += "])";
	}

	line += "{";

	return line;
}


EasyScript::UnknownElseCommand::UnknownElseCommand(State& state, int32_t value)
	: CommandBase<UnknownElseCommand>(state) {
	cmd->code = static_cast<Code>(value);

	Code code_parent;

	// Not really "Unknown", the list of parent commands is hardcoded here
	if (cmd->code == Code::ElseBranch) {
		code_parent = Code::ConditionalBranch;
	} else if (cmd->code == Code::ElseBranch_B) {
		code_parent = Code::ConditionalBranch_B;
	} else if (cmd->code == Code::VictoryHandler || cmd->code == Code::EscapeHandler || cmd->code == Code::DefeatHandler) {
		code_parent = Code::EnemyEncounter;
	} else if (cmd->code == Code::Transaction || cmd->code == Code::NoTransaction) {
		code_parent = Code::OpenShop;
	} else if (cmd->code == Code::NoStay) {
		code_parent = Code::Stay;
	} else {
		assert(false);
	}

	auto& commands = state.commands;
	for (auto it = commands.rbegin() + 1; it != commands.rend(); ++it) {
		if ((*it)->indent == state.indent) {
			if ((*it)->code == code_parent) {
				parent = it->get();
				break;
			}
		}
	}

	if (parent == nullptr) {
		throw std::runtime_error("ElseBranch has no parent");
	}

	state.indent++;
}

EasyScript::UnknownElseCommand EasyScript::UnknownElseCommand::String(std::string string) {
	cmd->string = string;
	return *this;
}

EasyScript::UnknownElseCommand EasyScript::UnknownElseCommand::Parameter(std::vector<int32_t> parameters) {
	cmd->parameters = parameters;
	return *this;
}

void EasyScript::UnknownElseCommand::Register(State& state) {
	auto& chai = state.chai;

	BindFunctions<UnknownElseCommand>(chai,
		&UnknownElseCommand::String, "string",
		&UnknownElseCommand::Parameter, "args");

	chai.add(chaiscript::fun([&state, &chai](int32_t value) {
		chai.add(chaiscript::fun([&state]() {
			auto end_command = std::make_shared<EventCommand>();
			end_command->code = Code::END;
			end_command->indent = state.indent;
			state.commands.push_back(end_command);
			state.indent--;
		}), "#block_end");

		return UnknownBranchCommand(state, value);
	}), "@branch_else");
}

std::optional<std::string> EasyScript::UnknownElseCommand::StringFromCommand(const EventCommandList& commands, size_t index, const EventCommand& parent) {
	std::string line;
	auto& this_cmd = *commands[index];
	int child_count = 0;

	if (index > 0) {
		--index;
	}

	for (auto it = std::make_reverse_iterator(commands.begin() + index); it != commands.rend(); ++it) {
		auto& cmd = **it;
		if (cmd.indent == this_cmd.indent) {
			if (cmd.code == parent.code && &cmd == &parent) {
				break;
			} else {
				// No sanity check for bad commands here
				++child_count;
			}
		}
	}

	line += std::format("@case(\"{}\") {{", this_cmd.GetEscapedString());

	return line;
}
