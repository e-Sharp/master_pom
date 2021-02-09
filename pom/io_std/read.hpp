#pragma once

#include <fstream>
#include <iterator>
#include <stdexcept>
#include <vector>

namespace pom {
namespace io_std {

void throw_if_bad(const std::ios& s) {
	if(s.bad()) throw std::runtime_error{
		"Bad stream."};
}

void throw_if_failed(const std::ios& s) {
	if(s.fail()) throw std::runtime_error{
		"Stream failed."};
}

template<typename Ty>
Ty read(std::istream& is) {
	auto r = Ty{};
	is.read(reinterpret_cast<char*>(&r), sizeof(Ty));
	throw_if_failed(is);
	return r;
}

template<typename It>
void read_until_eof(std::istream& is, It output) {
	while(!is.eof()) {
		*output = read<std::iterator_traits<It>::value_type>(is);
		++output;
		is.peek();
	}
}

std::size_t size(std::istream& is) {
	auto pos = is.tellg();
	is.ignore(std::numeric_limits<std::streamsize>::max());
	auto c = is.gcount();
	is.seekg(pos);
	return c;
}

}}
