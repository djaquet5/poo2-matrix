//
// Created by David on 21.02.2019.
//

#pragma once

#include "Operator.hpp"

class Sub : public Operator {
public:
    size_t apply(size_t leftValue, size_t rightValue, size_t modulo) const {
        // Stock a resilt in a long long to fit for a size_t
        long long result = leftValue - rightValue;

        // Get a real modulo. Example : -1 % 5 = 0, but it should be 4
        return (((result % (int) modulo) + modulo) % modulo);
    }
};
