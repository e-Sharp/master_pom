#pragma once

#include <fstream>
#include <stdexcept>

namespace pom {
namespace io {

std::fstream open_file(const char* filename, std::ios::openmode mode) {
	auto f = std::fstream{filename, mode};
	if(!f.is_open()) throw std::runtime_error{
		std::string{"Failed to open file "} + filename + "."};
	return f;
}

}}
