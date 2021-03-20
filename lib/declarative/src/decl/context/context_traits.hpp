#pragma once

namespace decl {
namespace detail {

template<typename Tr>
concept context_traits = requires {
	Tr::storage_traits;
	Tr::target;
};

}}
