#pragma once

namespace decl {
namespace detail {

template<typename Tr>
concept bound_storage_traits = requires {
	Tr::storage_traits;
	Tr::bound_targets;
};

}}
