#pragma once

#include <iterator>

namespace pom {
namespace maths_impl {

template<typename Range>
class vector_view {
public:
	explicit vector_view(Range&& r, std::size_t size)
		: range_{std::move(r)}
		, size_{size}
	{}

	constexpr std::size_t size() const noexcept {
		return size_;
	}

	// Iterators.

	constexpr auto begin() const {
		return std::begin(range_);
	}

	constexpr auto end() const {
		return std::end(range_);
	}

private:
	Range range_;
	std::size_t size_;
};

// Deduction guides.

template<typename R>
vector_view(R&&) -> vector_view<R>;

// Element access.

template<typename R, typename Index> constexpr
decltype(auto) at(const vector_view<R>& v, Index i) {
	auto it = v.begin();
	std::advance(it, i);
	return *it;
}

}}
