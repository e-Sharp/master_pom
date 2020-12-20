#pragma once

#include "pom/ctree/ctree.hpp"

#include <cmath>

class addition_op : public ctree {
public:
    addition_op(const shared_ctree& lhs, const shared_ctree& rhs)
        : lhs{lhs}
        , rhs{rhs}
    {}

    eval eval_at(point p) const override {
        auto le = lhs->eval_at(p);
        auto re = rhs->eval_at(p);
        return {
            .height = 0,
            .weight = 0
        };
    }

private:
    shared_ctree lhs;
    shared_ctree rhs;
};
