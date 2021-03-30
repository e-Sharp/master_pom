struct height_ {};
struct value_ {};

#include <decl.hpp>

#include <cmath>
#include <iostream>

using namespace decl;
using namespace decl::detail;



struct vec2f {};

struct distortion {};

template<typename DeclContext> constexpr
vec2f recipe(DeclContext, value_, distortion d, vec2f xy) {
	return {};
}

template<typename Terrain>
struct noise_warped {
	Terrain terrain;
	distortion distortion = {};
};

template<typename T>
noise_warped(T&&) -> noise_warped<T>;

template<typename T>
auto prerequisites(value_, noise_warped<T>&, vec2f) -> decl::targets<>;

template<typename DeclContext, typename T>
vec2f recipe(DeclContext, value_, noise_warped<T>& w, vec2f xy) {
	// decl::make<value_>(w.distortion, xy);
	return {};
}

template<typename T>
auto prerequisites(height_, const noise_warped<T>&, vec2f) -> decl::targets<value_>;

template<typename DeclContext, typename T>
float recipe(DeclContext c, height_, const noise_warped<T>& w, vec2f xy) {
	// c.ref<value_>();
	return 0.f;
}

int main() {
	auto ter = noise_warped(vec2f());
	make<height_>(ter, vec2f());
}
