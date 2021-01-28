#include "pom/maths/matrix/all.hpp"

#include <iomanip>
#include <iostream>

using namespace pom;

int main() {
	auto dm = dynamic_matrix<int>{col{3}, row{2}};
	auto sm = static_matrix<int, col{4}, row{3}>{};

	at(dm, col{2}, row{1}) = 3;

	for(row r = {0}; r < size(dm, row{}); r = row{r + 1}) {
		std::cout << "| ";
		for(col c = {0}; c < size(dm, col{}); c = col{c + 1}) {
			std::cout << std::setw(8) << at(dm, c, r) << " ";
		}
		std::cout << "|" << std::endl;
	}
}
