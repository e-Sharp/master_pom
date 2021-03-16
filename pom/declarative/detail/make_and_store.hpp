#pragma once

#include <pom/meta/type/type.hpp>
#include <pom/meta/type_list/type_list.hpp>

namespace pom {
namespace decl {
namespace detail {

template<typename C, typename What, typename... Args>
auto make_and_store(context<C>& c, meta::type<What> t, Args&&... args) {
	make(static_cast<const context<C>&>(c), t, std::forward<Args>(args)...);
	// std::get<What>(c.data) = make_(static_cast<const context<C>&>(c), t, std::forward<Args>(args)...);
}

template<typename C, typename... What, typename... Args>
auto make_and_store(context<C>& c, meta::type_list<What...>, Args&&... args) {
	(
		make_and_store(c, meta::type<What>(), std::forward<Args>(args)...)
	, ...);
}

}}}
