#pragma once

#include "pom/ctree/ctree.hpp"

#include <cmath>

class replacement_op : public ctree {
public:
    replacement_op(const shared_ctree& lhs, const shared_ctree& rhs)
        : lhs{lhs}
        , rhs{rhs}
    {}

    eval eval_at(point p) const override {
        auto le = lhs->eval_at(p);
        auto re = rhs->eval_at(p);
        return {
            .height = std::lerp(le.height, re.height, re.weight),
            .weight = le.weight
        };
    }

private:
    shared_ctree lhs;
    shared_ctree rhs;
};
