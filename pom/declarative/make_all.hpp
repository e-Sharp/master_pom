#pragma once

#include "detail/make_and_store.hpp"
#include "detail/make_sequence.hpp"
#include "context.hpp"

#include <pom/meta/type/type.hpp>

//

#include "data.hpp"

#include <pom/meta/type/all.hpp>

#include <iostream>

namespace pom {
namespace decl {

//template<typename... What, typename... Args>
//auto make(Args&&... args) {
//	constexpr auto ms = detail::make_sequence(type_list<What...>());
//	auto c = context(ms);
//	detail::make_and_store(c, ms, std::forward<Args>(args)...);
//	return c;
//}

template<typename... What, typename... Args>
auto make_all(Args&&... args) {
	constexpr auto ms = detail::make_sequence(type_list<What...>());
	std::cout << ms << std::endl;
	auto d = data_of(ms, args...);
	std::cout << d << std::endl;
}

}}
