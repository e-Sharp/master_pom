#pragma once

namespace decl {
namespace detail {

template<typename Tr>
concept storage_traits = requires {
	Tr::targets;
	Tr::recipes;
};

}}
