#pragma once

#include "pom/maths_impl/all.hpp"

namespace pom {
namespace terrain {

struct context {
	float gradient_epsilon = 0.1f;
	float weight_threshold = 0.f;
};



}}
