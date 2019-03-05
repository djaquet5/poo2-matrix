//
// Created by David on 21.02.2019.
//

#pragma once

#include "Operator.hpp"

class Mult : public Operator {
public:
    size_t apply(size_t leftValue, size_t rightValue, size_t modulo) const {
        return (leftValue * rightValue) % modulo;
    }
};
