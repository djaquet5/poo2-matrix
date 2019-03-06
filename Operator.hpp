/*
 -----------------------------------------------------------------------------------
 Laboratoire : 01
 Fichier     : Operator.hpp
 Auteur(s)   : David Jaquet & Christoph Rueff
 Date        : 06.03.2019

 Remarque(s) : - The result will be in the closed interval between 0 and modulo - 1

 -----------------------------------------------------------------------------------
*/

#pragma once

/**
 * Mother class of all the operator
 */
class Operator {
public:
    /**
     * Apply the operation, the result is in the closed interval between 0 and modulo - 1
     *
     * @param leftValue     Left value of the operation
     * @param rightValue    Right value of the operation
     * @param modulo        Modulo for the operation
     * @return Result of the operation
     */
    virtual size_t apply(size_t leftValue, size_t rightValue, size_t modulo) const = 0;
};
