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

#pragma once

#include "easyscript/forward.h"
#include "easyscript/parameter.h"
#include "command_base.h"

#include <optional>

namespace EasyScript {

class ShowChoiceOption;

class ShowChoice : public CommandBase<ShowChoice> {
public:
	ShowChoice(EasyScript::State& state, const std::string& label);

	ShowChoice Cancel();

	static void Register(State& state);

	static constexpr std::array name = { "ShowChoice", "message", "choice" };
	static constexpr Code code = Code::ShowChoice;

	static std::optional<std::string> StringFromCommand(const EventCommandList& commands, size_t index);
};

class ShowChoiceOption : public CommandBase<ShowChoiceOption> {
public:
	ShowChoiceOption(EasyScript::State& state, const std::string& label, bool is_cancel);

	ShowChoiceOption Cancel();

	static void Register(State& state);

	static constexpr std::array name = { "ShowChoiceOption", "message", "choice" };
	static constexpr Code code = Code::ShowChoiceOption;

	static std::optional<std::string> StringFromCommand(const EventCommandList& commands, size_t index, const EventCommand& parent);

private:
	int child_num = 0;
	bool is_cancel;
	EasyScript::EventCommand* parent = nullptr;
};


}
