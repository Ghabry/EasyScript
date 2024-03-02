#include "unknown_command.h"
#include "chaiscript/chaiscript.hpp"
#include "easyscript/binding.h"
#include "easyscript/event_command.h"
#include <format>

EasyScript::UnknownCommand::UnknownCommand(int32_t value) {
	cmd->SetDefaults(static_cast<Code>(value), "", { });
}

EasyScript::UnknownCommand EasyScript::UnknownCommand::String(std::string string) {
	cmd->string = string;
	return *this;
}

EasyScript::UnknownCommand EasyScript::UnknownCommand::Parameter(std::vector<int32_t> parameters) {
	cmd->parameters = parameters;
	return *this;
}

void EasyScript::UnknownCommand::Register(chaiscript::ChaiScript& chai, EventCommandList& commands) {
	BindConstructors<UnknownCommand, UnknownCommand(int32_t)>(chai, "UnknownCommand");
	BindFunctions<UnknownCommand>(chai,
		&UnknownCommand::String, "string",
		&UnknownCommand::Parameter, "args",
		[&](int32_t value){
			auto evt = UnknownCommand(value);
			commands.push_back(evt.cmd);
			return evt;
		}, "@command"
	);
}

std::optional<std::string> EasyScript::UnknownCommand::StringFromCommand(const EventCommand& command) {
	std::string line = std::format("@command({})", static_cast<int>(command.code));

	if (!command.string.empty()) {
		line += std::format(".string(\"{}\")", command.string);
	}

	if (!command.parameters.empty()) {
		line += ".args([";
		for (auto& parameter: command.parameters) {
			line += std::to_string(parameter) + ",";
		}
		line.pop_back();
		line += "])";
	}

	return line;
}
