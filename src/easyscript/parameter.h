#pragma once

#include "forward.h"

namespace EasyScript {

struct Parameter {
	const char* name;
	const int32_t default_val = -1;
	const int32_t val_idx = -1;
	const int32_t mode_idx = -1;
	const int32_t mode_shift = -1;

	bool IsDefault(const EventCommand& command) const;
	std::string ToString(const EventCommand& command, bool prefix_name = true) const;
	int32_t GetMode(const EventCommand& command) const;
	int32_t GetValue(const EventCommand& command) const;
	std::array<int32_t, 2> GetValueAndMode(const EventCommand& command) const;
	void Set(EventCommand& command, EasyScript::VariableArg value) const;
	void Set(EventCommand& command, int32_t value) const;
};

struct StringParameter {
	const char* default_val = nullptr;
	const int32_t val_idx = -1;
	const int32_t mode_idx = -1;
	const int32_t mode_shift = -1;

	bool IsDefault(const EventCommand& command) const;
	std::string ToString(const EventCommand& command) const;
	int32_t GetMode(const EventCommand& command) const;
	void Set(EventCommand& command, EasyScript::StringArg value) const;
	void Set(EventCommand& command, const std::string& value) const;
};

}
