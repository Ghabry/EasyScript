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


#include <format>
#include <memory>
#include <vector>
#include <iostream>
#include <lcf/rpg/eventcommand.h>
#include <lcf/lmu/reader.h>

#include "chaiscript/chaiscript.hpp"
#include "chaiscript/language/chaiscript_common.hpp"
#include "easyscript/all_commands.h"
#include "easyscript/event_command.h"
#include "easyscript/from_command.h"
#include "easyscript/state.h"
#include "easyscript/types.h"

int main() {
	EasyScript::State state;
	chaiscript::ChaiScript& chai = state.chai;
	EasyScript::EventCommandList& commands = state.commands;

	chai.add(chaiscript::vector_conversion<std::vector<int32_t>>());

	EasyScript::EventCommand::RegisterAll(state);

	for (int i = 0; i < 60; ++i) {
		auto map = lcf::LMU_Reader::Load(std::format("testgame/TestGame-2000/Map00{:02}.lmu", i));

		if (!map) {
			continue;
		}

		std::cout << "Map " << i << "\n";

		for (auto& event: map->events) {
			for (auto& page: event.pages) {
				//std::cout << std::format("{} (id={}, page={})\n", lcf::ToString(event.name), event.ID, page.ID);

				commands = {};
				auto event_lines = EasyScript::FromCommandList(page.event_commands);
				std::string script;
				for (auto& line: event_lines) {
					//std::cout << line << "\n";
					script += line += "\n";
				}

				try {
					size_t commands_size = commands.size();
					chai.eval(script);
				} catch (chaiscript::exception::eval_error& e) {
					std::cerr << std::format("{}", e.pretty_print());
					return 1;
				}

				bool has_error = false;
				auto error_fn = [&](std::string_view error_msg, size_t index, auto left, auto right) {
					std::cerr << std::format("{} (id={}, page={}) {}: {} != {}\n", lcf::ToString(event.name), event.ID, page.ID, error_msg, left, right);
					std::cerr << "Bad command: " << event_lines[index];
					has_error = true;
				};

				if (page.event_commands.size() != commands.size()) {
					std::cerr << std::format("Size mismatch (id={}, page={}) {}: {} != {}\n", lcf::ToString(event.name), event.ID, page.ID, page.event_commands.size(), commands.size());
					break;
				}

				size_t max_value = std::min(page.event_commands.size(), commands.size());
				for (size_t i = 0; i < max_value; ++i) {
					const auto& orig = page.event_commands[i];
					const auto& gen = commands[i];

					if (orig.code != static_cast<int32_t>(gen->code)) {
						error_fn(std::format("Code mismatch @ line {}", i), i, orig.code, static_cast<int32_t>(gen->code));
					}

					if (orig.indent != gen->indent) {
						error_fn(std::format("Indent mismatch @ line {}", i), i, orig.indent, gen->indent);
					}

					if (orig.string != gen->string) {
						error_fn(std::format("String mismatch @ line {}", i), i, lcf::ToString(orig.string), gen->string);
					}

					if (std::vector<int32_t>(orig.parameters.begin(), orig.parameters.end()) != gen->parameters) {
						std::string left = "[";
						for (auto& p: orig.parameters) {
							left += std::to_string(p) + ",";
						}
						left.pop_back();
						left += "]";

						std::string right = "[";
						for (auto& p: gen->parameters) {
							right += std::to_string(p) + ",";
						}
						right.pop_back();
						right += "]";
						error_fn(std::format("Parameter mismatch @ line {}", i + 1), i, left, right);
					}
				}

				if (has_error) {
					break;
				}
			}
		}
	}

	return 0;
}
