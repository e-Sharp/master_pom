#pragma once

#include "pom/ctree/ctree.hpp"

template<typename F, typename G>
class disc_prim : public ctree {
public:
    disc_prim(F height_f, G weight_f)
        : height_f{std::move(height_f)}
        , weight_f{std::move(weight_f)}
    {}

    eval eval_at(point p) const override {
        return {
            .height = height_f(p),
            .weight = weight_f(p)
        };
    }

private:
    F height_f;
    G weight_f;
};
