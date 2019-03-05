//
// Created by David on 21.02.2019.
//

#pragma once

#include "Operator.hpp"

class Sub : public Operator {
public:
    size_t apply(size_t leftValue, size_t rightValue, size_t modulo) const {
        long int result = leftValue - rightValue;
        return (((result % (int) modulo) + modulo) % modulo);
    }
};
