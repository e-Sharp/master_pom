#pragma once

#include "opposed.hpp"

#include "pom/terrain/function/tag/value.hpp"
#include "pom/terrain/import/all.hpp"

namespace pom::terrain {

template<typename DeclContext, typename O> constexpr
float recipe(DeclContext, value, const opposed<O>& o, vec2f xy) {
	return - get<0>(decl::make<value>(static_cast<const O&>(o), xy));
}

}
