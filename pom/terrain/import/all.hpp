#pragma once

#include "vec/vec.hpp"
#include "vec/xyz.hpp"

#include "pom/terrain/tag/all.hpp"

#include <decl.hpp>
#include <pom/maths/all.hpp>

namespace pom::terrain {

template<typename Ty>
using interval = maths::interval<Ty>;

template<typename Ty>
using mat = maths::dynamic_matrix<Ty>;

}