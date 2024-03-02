#pragma once

#include "forward.h"

#include <string>

namespace lcf::rpg {
	class EventCommand;
}

namespace EasyScript {

class EventCommand;

std::vector<std::string> FromCommandList(const EventCommandList& commands);
std::vector<std::string> FromCommandList(const std::vector<lcf::rpg::EventCommand>& commands);

std::string FromCommand(const EventCommand& command);
std::string FromCommand(const lcf::rpg::EventCommand& command);

}
