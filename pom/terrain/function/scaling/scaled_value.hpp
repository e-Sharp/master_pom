#pragma once

#include "scaled.hpp"

#include "pom/terrain/function/tag/value.hpp"
#include "pom/terrain/import/all.hpp"

namespace pom::terrain {

template<typename DeclContext, typename S> constexpr
float recipe(DeclContext, value, const scaled<S>& s, vec2f xy) {
	auto [v] = decl::make<value>(static_cast<const S&>(s), xy / s.scaling.value);
	return v;
}

}
