//
// Created by David on 21.02.2019.
//

#pragma once


#include <cstdio>

class Operator {
    virtual size_t apply(size_t leftValue, size_t rightValue);
};
