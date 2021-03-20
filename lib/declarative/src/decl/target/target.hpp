#pragma once

#include <type_traits>

namespace decl {

template<typename Ty>
concept target = std::is_empty_v<Ty>;

}
