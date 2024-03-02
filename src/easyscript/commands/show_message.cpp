#include "show_message.h"
#include "chaiscript/chaiscript.hpp"
#include "easyscript/binding.h"
#include "easyscript/event_command.h"
#include "easyscript/utils.h"
#include <format>
#include <sstream>

EasyScript::ShowMessage::ShowMessage(EasyScript::EventCommandList& commands, const std::string& value) :
	commands(commands) {

	std::istringstream ss(std::string{value});
	std::string line;

	bool first = true;

	while (Utils::ReadLine(ss, line)) {
		auto cmd = std::make_shared<EventCommand>();
		if (first) {
			cmd->SetDefaults(Code::ShowMessage, line, {});
			first = false;
		} else {
			cmd->SetDefaults(Code::ShowMessage_2, line, {});
		}
		commands.push_back(cmd);
	}

	if (commands.empty()) {
		auto cmd = std::make_shared<EventCommand>();
		cmd->SetDefaults(Code::ShowMessage, "", {});
		commands.push_back(cmd);
	}

	cmd_end = commands.back();
}

EasyScript::ShowMessage EasyScript::ShowMessage::Line(const std::string& value) {
	auto cmd = std::make_shared<EventCommand>();
	cmd->SetDefaults(Code::ShowMessage_2, value, {});

	auto it = std::find(commands.begin(), commands.end(), cmd_end);
	commands.insert(std::next(it), cmd);
	cmd_end = cmd;

	return *this;
}

void EasyScript::ShowMessage::Register(chaiscript::ChaiScript& chai, EventCommandList& commands) {
	BindConstructors<ShowMessage, ShowMessage(EasyScript::EventCommandList&, const std::string&)>(
		chai, "ShowMessage");

	BindFunctions<ShowMessage>(chai,
		&ShowMessage::Line, "line",
		[](ShowMessage& obj) {
			return obj.Line("");
		}, "newline"
	);

	BindNamespaceFunctions(
		chai, "message",
		[&](const std::string& value){
			auto evt = ShowMessage(commands, value);
			return evt;
		}, "show"
	);
}

std::optional<std::string> EasyScript::ShowMessage::StringFromCommand(EventCommandList& commands) {
	assert(!commands.empty());

	std::string line = std::format("@message.show(\"{}\")", commands[0]->GetEscapedString());

	for (auto& command: std::span(commands).subspan(1)) {
		if (command->string.empty()) {
			line += "\n  .newline";
		} else {
			line += std::format("\n  .line(\"{}\")", command->GetEscapedString());
		}
	}

	return line;
}
