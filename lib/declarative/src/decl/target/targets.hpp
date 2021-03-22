#pragma once

#include "decl/target/target.hpp"
#include "decl/type_list/type_list.hpp"

namespace decl {

template<target... TL>
struct targets : type_list<TL...> {};

}
