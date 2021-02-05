#pragma once

#include "pom/maths/matrix/all.hpp"
#include "pom/maths/preset/default/all.hpp"

namespace pom {
namespace terrain {

using namespace pom::maths::default_preset;

struct heightfield {
	static_vector<interval<float>, 2> domain = {};
	dynamic_matrix<float> heights = {};
};

}}
