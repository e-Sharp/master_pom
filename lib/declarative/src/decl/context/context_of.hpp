#pragma once

#include "context.hpp"

#include "decl/storage/storage.hpp"
#include "decl/type/type.hpp"

namespace decl {
namespace detail {

template<typename S, typename Target>
auto context_of(storage<S>& s, type<Target>) {
	struct traits {
		using storage_traits = S;
		using target = Target;
	};
	return context<traits>(s);
}

}}
