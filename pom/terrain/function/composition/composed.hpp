#pragma once

namespace pom::terrain {

template<typename First, typename Second>
struct composed {
	First first;
	Second second;
};

template<typename F, typename S>
composed(F, S) -> composed<F, S>;

}
