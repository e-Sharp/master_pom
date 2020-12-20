#pragma once

#include "pom/ctree/ctree.hpp"

#include <memory>

template<typename F>
class warping_op : public ctree {
public:
    warping_op(F f, const std::shared_ptr<ctree>& subtree)
        : f{std::move(f)}
        , subtree{subtree}
    {}

    eval eval_at(point p) const override {
        return subtree->eval_at(f(p));
    }

private:
    F f;
    std::shared_ptr<ctree> subtree;
};
