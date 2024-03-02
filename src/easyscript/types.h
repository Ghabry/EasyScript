#pragma once

namespace chaiscript {
	class ChaiScript;
}

namespace EasyScript {

class Variable {
public:
	Variable(int id) : id(id) {}

	static void Register(chaiscript::ChaiScript& chai);

	int id = 0;
};

class VariableIndirect {
public:
	VariableIndirect(int id) : id(id) {}

	static void Register(chaiscript::ChaiScript& chai);

	int id = 0;
};

class Switch {
public:
	Switch(int id) : id(id) {}

	static void Register(chaiscript::ChaiScript& chai);

	int id = 0;
};

class SwitchIndirect {
public:
	SwitchIndirect(int id) : id(id) {}

	static void Register(chaiscript::ChaiScript& chai);

	int id = 0;
};

class String {
public:
	String(int id) : id(id) {}

	static void Register(chaiscript::ChaiScript& chai);

	int id = 0;
};

class StringIndirect {
public:
	StringIndirect(int id) : id(id) {}

	static void Register(chaiscript::ChaiScript& chai);

	int id = 0;
};

void RegisterTypes(chaiscript::ChaiScript& chai);

}
