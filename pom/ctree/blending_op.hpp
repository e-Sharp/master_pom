#pragma once

#include "pom/ctree/ctree.hpp"

#include <cmath>

class blending_op : public ctree {
public:
    blending_op(const shared_ctree& lhs, const shared_ctree& rhs)
        : lhs{lhs}
        , rhs{rhs}
    {}

    eval eval_at(point p) const override {
        auto le = lhs->eval_at(p);
        auto re = rhs->eval_at(p);
        return {
            .height = (le.height * le.weight + re.height * re.weight) / (le.weight + re.weight),
            .weight = le.weight + re.weight
        };
    }

private:
    shared_ctree lhs;
    shared_ctree rhs;
};
