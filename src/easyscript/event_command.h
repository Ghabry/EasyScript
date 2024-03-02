#pragma once

#include <string>
#include <string_view>
#include <vector>
#include <cstdint>

#include "forward.h"

namespace EasyScript {

class EventCommand {
public:
	EventCommand() = default;

	void SetDefaults(Code code, std::string_view string, std::initializer_list<int32_t> parameters);

	std::string GetEscapedString() const;

	static void RegisterAll(chaiscript::ChaiScript& chai, EventCommandList& commands);

	Code code = static_cast<Code>(0);
	int32_t indent = 0;
	std::string string;
	std::vector<int32_t> parameters;
};

}
