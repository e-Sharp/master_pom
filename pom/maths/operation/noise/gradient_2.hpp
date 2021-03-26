#pragma once

namespace pom::maths {

template<typename Hash>
struct gradient_noise_2 {
	gradient_noise_2(Hash&& h) : hash(std::move(h)) {}

	Hash hash;
};

template<typename H>
gradient_noise_2(H&&) -> gradient_noise_2<H>;

}
