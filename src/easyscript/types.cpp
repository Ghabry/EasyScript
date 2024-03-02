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
