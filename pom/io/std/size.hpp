#pragma once

#include <istream>
#include <limits>

namespace pom {

std::size_t size(std::istream& is) {
	auto pos = is.tellg();
	is.ignore(std::numeric_limits<std::streamsize>::max());
	auto c = is.gcount();
	is.seekg(pos);
	return c;
}

} // namespace pom
