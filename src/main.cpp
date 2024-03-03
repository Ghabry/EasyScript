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


#include <memory>
#include <vector>
#include <iostream>
#include <lcf/rpg/eventcommand.h>
#include <lcf/lmu/reader.h>

#include "chaiscript/chaiscript.hpp"
#include "easyscript/all_commands.h"
#include "easyscript/event_command.h"
#include "easyscript/from_command.h"
#include "easyscript/state.h"
#include "easyscript/types.h"

int main() {
	chaiscript::ChaiScript chai;
	chai.add(chaiscript::vector_conversion<std::vector<int32_t>>());

	EasyScript::State state;
	EasyScript::EventCommandList& commands = state.commands;

	EasyScript::EventCommand::RegisterAll(chai, state);

	chai.eval(R"(
		@message.show("Msg Line1")
			.line("Msg Line2") {
			@message.show("Msg2 Line1")
				.line("Msg2 Line2")
		}
	)");

	auto map = lcf::LMU_Reader::Load("Map0001.lmu");

	int event_id = 1;
	int page_id = 1;
	std::string event_name = "EV0002";

	for (auto& events: map->events) {
		if (events.name == event_name) {
			for (auto& page: events.pages) {
				if (page.ID == page_id) {
					for (auto& line: EasyScript::FromCommandList(page.event_commands)) {
						std::cout << line << "\n";
					}
				}
			}
		}
	}

	chai.eval(R"(
		@message.show("XTesting message speed:")
			.line("\\s[1]Speed 1A") {
			@message.show("XTesting message speed:")
				.line("\\s[1]Speed 1A")
		}
		@message.show("YTesting message speed:")
			.line("\\s[2]Speed 2B")
		@command(123).string("Alex").args([1,2,3])
		@command(345).string("Brian").args([100])
	)");

	/*chai.eval(R"(
		@battle.ce(10)
		@battle.ce($v(11))
		@battle.ce($vv(12))

		@music.play("Ship1").fadein(100)
		@music.play($t(100)).fadein($v(200)).tempo($vv(50)).balance(30).fadein(200)
		@music.stop
		@music.play($tv(200))

		@sound.play("Ship1")
		@sound.play($t(100)).tempo($vv(50)).balance(30)
		@sound.stop
		@sound.play($tv(200))

		@message.show("Hello").newline().line("World")
		@message.face("Actor2").left

		@message.options.top.font("A", 1).size(100, 200)
		@message.options.center.font("A", 1).size(100, 200)
		@message.options.bottom.font($t(42), 1).size(100, 200)

		@map.trigger.x(123).y(0)
		@map.trigger.x(123).y(345)
		@map.trigger.y($v(222)).x($vv(333))
  	)");*/

	for (auto& line: EasyScript::FromCommandList(state)) {
		std::cout << line << "\n";
	}

	return 0;
}
