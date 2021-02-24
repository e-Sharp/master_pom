#pragma once

#include <algorithm>

namespace pom {
namespace io {

template<typename Ty> constexpr
Ty reversed(Ty val) noexcept {
	auto data = reinterpret_cast<std::byte*>(&val);
	std::reverse(data, data + sizeof(Ty));
	return val;
}

}}
