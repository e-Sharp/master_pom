#pragma once

#include <pom/meta/type/type.hpp>
#include <pom/meta/type_list/type_list.hpp>

namespace pom {
namespace decl {

template<typename Ty> consteval
meta::type_list<> dependencies(meta::type<Ty>) { return {}; }

}}
