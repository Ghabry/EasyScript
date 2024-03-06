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

#include "parameter.h"
#include "easyscript/forward.h"
#include "easyscript/types.h"
#include "event_command.h"
#include "chaiscript/chaiscript.hpp"
#include <format>
#include <string>

static int32_t get_bitfield(const std::vector<int32_t>& parameters, int32_t index, int32_t shift) {
	return (parameters[index] & (0xF << shift * 4)) >> shift * 4;
}

static void set_bitfield(std::vector<int32_t>& parameters, int32_t index, int32_t shift, int32_t value) {
	parameters[index] &= ~(0xF << shift * 4);
	parameters[index] |= (value << shift * 4);
}

static void resize(std::vector<int32_t>& parameters, int32_t index) {
	if (parameters.size() <= index) {
		parameters.resize(index + 1);
	}
}

bool EasyScript::Parameter::IsDefault(const EventCommand& command) const {
	assert(val_idx >= 0);

	auto& parameters = command.parameters;

	int32_t mode = GetMode(command);
	if (mode != 0) {
		return false;
	}

	int32_t val = GetValue(command);

	return val == default_val;
}

std::string EasyScript::Parameter::ToString(const EventCommand& command, bool prefix_name) const {
	assert(val_idx >= 0);

	auto& parameters = command.parameters;

	auto [val, mode] = GetValueAndMode(command);

	std::string arg_str;
	switch (mode) {
		case 1:
			arg_str = "$v(" + std::to_string(val) + ")";
			break;
		case 2:
			arg_str = "$vv(" + std::to_string(val) + ")";
			break;
		default:
			arg_str = std::to_string(val);
			break;
		break;
	};

	if (prefix_name) {
		return std::format(".{}({})", name, arg_str);
	} else {
		return arg_str;
	}
}

int32_t EasyScript::Parameter::GetValue(const EventCommand& command) const {
	assert(val_idx >= 0);

	auto& parameters = command.parameters;

	int32_t val = default_val;
	if (parameters.size() > val_idx) {
		val = parameters[val_idx];
	}

	return val;
}

int32_t EasyScript::Parameter::GetMode(const EventCommand& command) const {
	auto& parameters = command.parameters;

	int32_t mode = 0;
	if (mode_idx >= 0 && parameters.size() > mode_idx) {
		if (mode_shift < 0) {
			mode = parameters[mode_idx];
		} else {
			mode = get_bitfield(parameters, mode_idx, mode_shift);
		}
	}

	return mode;
}

std::array<int32_t, 2> EasyScript::Parameter::GetValueAndMode(const EventCommand& command) const {
	return { GetValue(command), GetMode(command) };
}

void EasyScript::Parameter::Set(EventCommand& command, EasyScript::VariableArg value) const {
	assert(mode_idx >= 0);
	assert(val_idx >= 0);

	auto type = value.get_type_info();
	auto& parameters = command.parameters;

	if (type.bare_equal_type_info(typeid(int32_t))) {
		// int (no indirection)
		int32_t val = *value.get().cast<std::shared_ptr<const int32_t>>();
		Set(command, val);
	} else if (type.bare_equal_type_info(typeid(Variable))) {
		// In Variable
		resize(parameters, val_idx);
		resize(parameters, mode_idx);
		if (mode_shift < 0) {
			parameters[mode_idx] = 1;
		} else {
			set_bitfield(parameters, mode_idx, mode_shift, 1);
		}
		parameters[val_idx] = value.get().cast<std::shared_ptr<Variable>>()->id;
	} else if (type.bare_equal_type_info(typeid(VariableIndirect))) {
		// Indirect Variable
		resize(parameters, val_idx);
		resize(parameters, mode_idx);
		if (mode_shift < 0) {
			parameters[mode_idx] = 2;
		} else {
			set_bitfield(parameters, mode_idx, mode_shift, 2);
		}
		parameters[val_idx] = value.get().cast<std::shared_ptr<VariableIndirect>>()->id;
	} else {
		throw std::runtime_error("Unsupported Value Type");
	}
}

void EasyScript::Parameter::Set(EventCommand& command, int32_t value) const {
	assert(val_idx >= 0);

	auto& parameters = command.parameters;
	resize(parameters, val_idx);

	if (mode_idx >= 0 && parameters.size() > mode_idx) {
		if (mode_shift < 0) {
			parameters[mode_idx] = 0;
		} else {
			set_bitfield(parameters, mode_idx, mode_shift, 0);
		}
	}
	parameters[val_idx] = value;
}

bool EasyScript::StringParameter::IsDefault(const EventCommand& command) const {
	auto& parameters = command.parameters;

	int32_t mode = 0;
	if (mode_idx >= 0 && parameters.size() > mode_idx) {
		mode = parameters[mode_idx];
	}

	if (mode != 0) {
		return false;
	}

	return command.string == default_val;
}

std::string EasyScript::StringParameter::ToString(const EventCommand& command) const {
	auto& parameters = command.parameters;

	int32_t mode = GetMode(command);

	int16_t val = 0;
	if (mode > 0 && parameters.size() > val_idx) {
		val = parameters[val_idx];
	}

	std::string arg_str;
	switch (mode) {
		case 1:
			arg_str = "$t(" + std::to_string(val) + ")";
			break;
		case 2:
			arg_str = "$tv(" + std::to_string(val) + ")";
			break;
		default:
			arg_str = '"' + command.string + '"';
			break;
		break;
	};

	return "(" + arg_str + ")";
}

int32_t EasyScript::StringParameter::GetMode(const EventCommand& command) const {
	auto& parameters = command.parameters;

	int32_t mode = 0;
	if (mode_idx >= 0 && parameters.size() > mode_idx) {
		if (mode_shift < 0) {
			mode = parameters[mode_idx];
		} else {
			mode = get_bitfield(parameters, mode_idx, mode_shift);
		}
	}

	return mode;
}

void EasyScript::StringParameter::Set(EventCommand& command, EasyScript::StringArg value) const {
	assert(mode_idx >= 0);
	assert(val_idx >= 0);

	auto type = value.get_type_info();
	auto& parameters = command.parameters;

	if (type.bare_equal_type_info(typeid(std::string))) {
		// String (no indirection)
		std::string val = *value.get().cast<std::shared_ptr<const std::string>>();
		Set(command, val);
	} else if (type.bare_equal_type_info(typeid(String))) {
		// In Variable
		resize(parameters, val_idx);
		resize(parameters, mode_idx);
		if (mode_shift < 0) {
			parameters[mode_idx] = 1;
		} else {
			set_bitfield(parameters, mode_idx, mode_shift, 1);
		}
		parameters[val_idx] = value.get().cast<std::shared_ptr<String>>()->id;
		command.string.clear();
	} else if (type.bare_equal_type_info(typeid(StringIndirect))) {
		// Indirect Variable
		resize(parameters, val_idx);
		resize(parameters, mode_idx);
		if (mode_shift < 0) {
			parameters[mode_idx] = 2;
		} else {
			set_bitfield(parameters, mode_idx, mode_shift, 2);
		}
		parameters[val_idx] = value.get().cast<std::shared_ptr<StringIndirect>>()->id;
		command.string.clear();
	} else {
		throw std::runtime_error("Unsupported Value Type");
	}
}

void EasyScript::StringParameter::Set(EventCommand& command, const std::string& value) const {
	auto& parameters = command.parameters;
	resize(parameters, val_idx);

	if (mode_idx >= 0 && parameters.size() > mode_idx) {
		if (mode_shift < 0) {
			parameters[mode_idx] = 0;
		} else {
			set_bitfield(parameters, mode_idx, mode_shift, 0);
		}
	}
	command.string = value;
}
