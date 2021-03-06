/*
 -----------------------------------------------------------------------------------
 Laboratoire : 01
 Fichier     : Sub.hpp
 Auteur(s)   : David Jaquet & Christoph Rueff
 Date        : 06.03.2019

 Remarque(s) :

 -----------------------------------------------------------------------------------
*/

#pragma once

#include "Operator.hpp"

/**
 * Substraction operator
 */
class Sub : public Operator {
public:
    /**
     * Apply the substraction, the result is in the closed interval between 0 and modulo - 1
     *
     * @param leftValue     Left value of the operation
     * @param rightValue    Right value of the operation
     * @param modulo        Modulo for the operation
     * @return Result of the operation
     */
    size_t apply(size_t leftValue, size_t rightValue, size_t modulo) const {
        // Stock a result in a long long to fit for a size_t
        long long result = leftValue - rightValue;

        // Get a real modulo. Example : -1 % 5 = 0, but it should be 4
        return (((result % (int) modulo) + modulo) % modulo);
    }
};
