/*
 -----------------------------------------------------------------------------------
 Laboratoire : 01
 Fichier     : Add.hpp
 Auteur(s)   : David Jaquet & Christoph Rueff
 Date        : 06.03.2019

 Remarque(s) :

 -----------------------------------------------------------------------------------
*/

#pragma once

#include "Operator.hpp"

/**
 * Addition operator
 */
class Add : public Operator {
public:
    /**
     * Apply the addition, the result is in the closed interval between 0 and modulo - 1
     *
     * @param leftValue     Left value of the operation
     * @param rightValue    Right value of the operation
     * @param modulo        Modulo for the operation
     * @return Result of the operation
     */
    size_t apply(size_t leftValue, size_t rightValue, size_t modulo) const {
        return (leftValue + rightValue) % modulo;
    }
};