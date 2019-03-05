//
// Created by David on 21.02.2019.
//

#pragma once


#include <cstdio>

class Operator {
public:
    virtual size_t apply(size_t leftValue, size_t rightValue, size_t modulo) const = 0;
};
