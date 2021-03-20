#pragma once

#include "context_traits.hpp"

#include "decl/storage/storage.hpp"

namespace decl {

template<detail::context_traits Tr>
class context {
private:
	using storage_traits = typename Tr::storage_traits;

public:
	template<typename S> constexpr
	context(detail::storage<S>& s)
		: storage(s)
	{}
	
	template<typename Target> constexpr
	const auto& ref() const {
		// static_assert();
		return get(storage, type<Target>());
	}

private:
	detail::storage<storage_traits>& storage;
};

}
