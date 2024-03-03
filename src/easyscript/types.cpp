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

#include "types.h"
#include "chaiscript/chaiscript.hpp"

void EasyScript::Variable::Register(chaiscript::ChaiScript& chai) {
	chaiscript::ModulePtr m = std::make_shared<chaiscript::Module>();
	chaiscript::utility::add_class<Variable>(*m, "$v",
	{
		chaiscript::constructor<Variable(int)>(),
	},
	{
	}
	);
	chai.add(m);
}

void EasyScript::VariableIndirect::Register(chaiscript::ChaiScript& chai) {
	chaiscript::ModulePtr m = std::make_shared<chaiscript::Module>();
	chaiscript::utility::add_class<VariableIndirect>(*m, "$vv",
	{
		chaiscript::constructor<VariableIndirect(int)>(),
	},
	{
	}
	);
	chai.add(m);
}

void EasyScript::Switch::Register(chaiscript::ChaiScript& chai) {
	chaiscript::ModulePtr m = std::make_shared<chaiscript::Module>();
	chaiscript::utility::add_class<Switch>(*m, "$s",
	{
		chaiscript::constructor<Switch(int)>(),
	},
	{
	}
	);
	chai.add(m);
}

void EasyScript::SwitchIndirect::Register(chaiscript::ChaiScript& chai) {
	chaiscript::ModulePtr m = std::make_shared<chaiscript::Module>();
	chaiscript::utility::add_class<SwitchIndirect>(*m, "$sv",
	{
		chaiscript::constructor<SwitchIndirect(int)>(),
	},
	{
	}
	);
	chai.add(m);
}

void EasyScript::String::Register(chaiscript::ChaiScript& chai) {
	chaiscript::ModulePtr m = std::make_shared<chaiscript::Module>();
	chaiscript::utility::add_class<String>(*m, "$t",
	{
		chaiscript::constructor<String(int)>(),
	},
	{
	}
	);
	chai.add(m);
}

void EasyScript::StringIndirect::Register(chaiscript::ChaiScript& chai) {
	chaiscript::ModulePtr m = std::make_shared<chaiscript::Module>();
	chaiscript::utility::add_class<StringIndirect>(*m, "$tv",
	{
		chaiscript::constructor<StringIndirect(int)>(),
	},
	{
	}
	);
	chai.add(m);
}

void EasyScript::RegisterTypes(chaiscript::ChaiScript& chai) {
	Variable::Register(chai);
	VariableIndirect::Register(chai);
	Switch::Register(chai);
	SwitchIndirect::Register(chai);
	String::Register(chai);
	StringIndirect::Register(chai);
}
