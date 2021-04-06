#pragma once

#include "pom/terrain/import/all.hpp"

namespace pom::terrain {

struct translation {
	translation() = delete;

	constexpr translation(vec2f xy) noexcept
		: value(std::move(xy))
	{}

	constexpr operator const vec2f&() noexcept {
		return value;
	}

	vec2f value;
};

}
