#pragma once

#include "bound_storage_traits.hpp"
#include "storage.hpp"

#include "decl/type_list/size.hpp"
#include "decl/type_list/type_list.hpp"

#include <tuple>

namespace decl {
namespace detail {

template<bound_storage_traits Tr>
struct bound_storage {
	using storage_traits = typename Tr::storage_traits;

	storage<storage_traits> storage = {};
};

}}
