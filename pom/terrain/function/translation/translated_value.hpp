#pragma once

#include "translated.hpp"

#include "pom/terrain/function/tag/value.hpp"
#include "pom/terrain/import/all.hpp"

namespace pom::terrain {

template<typename DeclContext, typename T> constexpr
float recipe(DeclContext, value, const translated<T>& t, vec2f xy) {
	auto [v] = decl::make<value>(
		static_cast<const T&>(t), 
		xy + t.translation.value);
	return v;
}

}
