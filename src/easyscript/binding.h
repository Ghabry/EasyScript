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

#include "forward.h"
#include "parameter.h"

#include "chaiscript/chaiscript.hpp"
#include <type_traits>

// TODO: Binding of Constants

namespace EasyScript {

namespace detail {
	template<typename Class>
	static Class SetFn(const EasyScript::Parameter& param, Class* cls, EasyScript::VariableArg value) {
		param.Set(*cls->cmd, value);
		return *cls;
	}

	template<typename Class>
	inline void AddFunction(chaiscript::ChaiScript&) {}

	template<typename Class, typename Function, typename... Next>
	void AddFunction(chaiscript::ChaiScript& chai, Function fn, const char* name, Next&...next) {
		chai.add(chaiscript::fun(fn), name);
		AddFunction<Class>(chai, next...);
	}

	template<typename Class, typename... Next>
	void AddFunction(chaiscript::ChaiScript& chai, const Parameter& parameter, Next&...next) {
		chai.add(chaiscript::fun(&SetFn<Class>, parameter), parameter.name);
		AddFunction<Class>(chai, next...);
	}

	inline void AddConstructor(chaiscript::ChaiScript&, const std::string&) {}

	template<typename Constructor, typename... Constructors>
	void AddConstructor(chaiscript::ChaiScript& chai, const std::string& class_name) {
		chai.add(chaiscript::constructor<Constructor>(), class_name);
		//AddConstructor<Constructors...>(chai, class_name); FIXME
	}

	template<typename Class, typename ConstructorArgType, typename Constructor>
	void AddNamespaceConstructor(chaiscript::ChaiScript& chai, EventCommandList& commands, std::string ns, const char* fn_name) {
		chaiscript::Boxed_Value fn;
		if constexpr (std::is_void<ConstructorArgType>()) {
			fn = chaiscript::var(chaiscript::fun([&]() {
				auto evt = Class();
				commands.push_back(evt.cmd);
				return evt;
			}));
		} else {
			fn = chaiscript::var(chaiscript::fun([&](ConstructorArgType arg) {
				auto evt = Class(arg);
				commands.push_back(evt.cmd);
				return evt;
			}));
		}

		if (chai.has_global(ns)) {
			auto o = chai.get_global(ns).get().cast<std::shared_ptr<chaiscript::dispatch::Dynamic_Object>>();
			(*o)[fn_name] = fn;
		} else {
			chaiscript::dispatch::Dynamic_Object o;
			o[fn_name] = fn;
			chai.set_global(chaiscript::var(o), ns);
		}
	}

	inline void AddNamespaceFunction(chaiscript::ChaiScript&, std::string) {}

	template<typename Function, typename... Next>
	void AddNamespaceFunction(chaiscript::ChaiScript& chai, std::string ns, Function fn, const char* fn_name, Next&...next) {
		auto ns_fn = chaiscript::var(chaiscript::fun(fn));

		if (chai.has_global("@" + ns)) {
			auto o = chai.get_global("@" + ns).get().cast<std::shared_ptr<chaiscript::dispatch::Dynamic_Object>>();
			(*o)[fn_name] = ns_fn;
		} else {
			chaiscript::dispatch::Dynamic_Object o;
			o[fn_name] = ns_fn;
			chai.set_global(chaiscript::var(o), "@" + ns);
		}

		AddNamespaceFunction(chai, ns, next...);
	}
}

template<typename Class>
constexpr void BindClass(
	chaiscript::ChaiScript& chai,
	const char* class_name) {

	chai.add(chaiscript::user_type<Class>(), class_name);
}

template<typename Class, typename Constructor, typename... Constructors>
constexpr void BindConstructors(chaiscript::ChaiScript& chai, std::string class_name) {
	class_name = "__cls_" + class_name;
    chai.add(chaiscript::user_type<Class>(), class_name);
	detail::AddConstructor<Constructor, Constructors...>(chai, class_name);
}

template<typename Class, typename... Functions>
constexpr void BindFunctions(
	chaiscript::ChaiScript& chai,
	Functions const&... f) {
	detail::AddFunction<Class>(chai, f...);
}

template<typename... Functions>
constexpr void BindNamespaceFunctions(
		chaiscript::ChaiScript& chai,
		std::string ns,
		Functions const&... f) {
	detail::AddNamespaceFunction(chai, ns, f...);
}

template<typename Class, typename ConstructorArgType, typename Constructor, typename... Constructors, typename... Functions>
void Bind(
		chaiscript::ChaiScript& chai,
		EasyScript::EventCommandList& commands,
		std::string class_name,
		std::string ns,
		const char* ns_fn,
		Functions const&... f) {
	class_name = "__cls_" + class_name;
	chai.add(chaiscript::user_type<Class>(), class_name);

	detail::AddConstructor<Constructor, Constructors...>(chai, class_name);
	detail::AddFunction<Class>(chai, f...);
	detail::AddNamespaceConstructor<Class, ConstructorArgType, Constructor>(chai, commands, "@" + ns, ns_fn);
}

template<typename Class, typename ConstructorArgType, typename Constructor, typename... Constructors>
void BindAuto(
		chaiscript::ChaiScript& chai,
		EasyScript::EventCommandList& commands) {

	Bind<Class, ConstructorArgType, Constructor, Constructors...>(
		chai, commands, Class::name[0], Class::name[1], Class::name[2]);

	if constexpr (requires { Class::param; } ) {
		for (auto& parameter: Class::param) {
			chai.add(chaiscript::fun(&detail::SetFn<Class>, parameter), parameter.name);
		}
	}
}

}
