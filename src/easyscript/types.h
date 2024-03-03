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
