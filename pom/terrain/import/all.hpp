#pragma once

#include "noise/gradient_noise.hpp"
#include "vec/vec.hpp"
#include "vec/xyz.hpp"

#include <decl.hpp>
#include <pom/maths/all.hpp>
#include <pom/meta/exception/all.hpp>

namespace pom::terrain {

template<typename Ty>
using interval = maths::interval<Ty>;

template<typename Ty>
using mat = maths::dynamic_matrix<Ty>;

}
