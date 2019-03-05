//
// Created by David on 21.02.2019.
//

#pragma once

#include "Operator.hpp"

class Sub : public Operator {
public:
    size_t apply(size_t leftValue, size_t rightValue, size_t modulo) const {
        long int res = leftValue - rightValue;
        return (((res % (unsigned int) modulo) + modulo) % modulo);
    }
};
