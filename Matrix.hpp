/*
 -----------------------------------------------------------------------------------
 Laboratoire : 01
 Fichier     : Matrix.hpp
 Auteur(s)   : David Jaquet & Christoph Rueff
 Date        : 06.03.2019

 Remarque(s) :

 -----------------------------------------------------------------------------------
*/

#pragma once

#include <string>
#include <iostream>
#include "Operator.hpp"

/**
 * Class who allow to do some operation on a matrix.
 */
class Matrix {
private:
    size_t nbLines;
    size_t nbColumns;
    size_t modulo;

    size_t** data;

public:
    /**
     * Create a matrix and fill it with random value
     *
     * @param nbLines       Number of lines of the matrix
     * @param nbColumns     Number of columns of the matrix
     * @param modulo        Modulo of the matrix
     */
    Matrix(size_t nbLines, size_t nbColumns, size_t modulo);

    /**
     * Create a matrix and fill it with given value
     *
     * @param nbLines       Number of lines of the matrix
     * @param nbColumns     Number of columns of the matrix
     * @param modulo        Modulo of the matrix
     * @param data          Values of the matrix
     */
    Matrix(size_t nbLines, size_t nbColumns, size_t modulo, size_t** data);

    /**
     * Copy a matrix
     *
     * @param other     Source matrix to do the copy
     */
    Matrix(const Matrix& other);

    /**
     * Destructor
     */
    virtual ~Matrix() {
        free();
    }

    /**
     * Overload of the << operator for the display
     *
     * @param ostream   Stream for the display
     * @param matrix    Matrix to display
     * @return          Stream with the matrix for the display
     */
    friend std::ostream& operator << (std::ostream& ostream, const Matrix& matrix);

    /**************************** Operations ****************************/
    /**
     * Get a pointer on a matrix who is the result of the addition between 2 matrices
     *
     * @param other     Other matrix to do the operation
     * @return Pointer on the result matrix
     */
    Matrix* add(const Matrix& other) const;

    /**
     * Get a pointer on a matrix who is the result of the substraction between 2 matrices
     *
     * @param other     Other matrix to do the operation
     * @return Pointer on the result matrix
     */
    Matrix* sub(const Matrix& other) const;

    /**
     * Get a pointer on a matrix who is the result of the multiplication between 2 matrices
     *
     * @param other     Other matrix to do the operation
     * @return Pointer on the result matrix
     */
    Matrix* mult(const Matrix& other) const;

    /**
     * Get a matrix who is the result of the addition between 2 matrices
     *
     * @param other     Other matrix to do the operation
     * @return Result matrix
     */
    Matrix addAndGetValue(const Matrix& other) const;

    /**
     * Get a matrix who is the result of the substraction between 2 matrices
     *
     * @param other     Other matrix to do the operation
     * @return Result matrix
     */
    Matrix subAndGetValue(const Matrix& other) const;

    /**
     * Get a matrix who is the result of the multiplication between 2 matrices
     *
     * @param other     Other matrix to do the operation
     * @return Result matrix
     */
    Matrix multAndGetValue(const Matrix& other) const;

    /**
     * Add the other matrix given to the current one
     *
     * @param other     Other matrix to do the operation
     * @return Current matrix
     */
    Matrix addOnThis(Matrix& other);

    /**
     * Substract the other matrix given to the current one
     *
     * @param other     Other matrix to do the operation
     * @return Current matrix
     */
    Matrix subOnThis(Matrix& other);

    /**
     * Multiply the other matrix given to the current one
     *
     * @param other     Other matrix to do the operation
     * @return Current matrix
     */
    Matrix multOnthis(Matrix& other);

private:

    /**
     * Execute the operation on the current matrix
     *
     * @param other     Other matrix to make the operation
     * @param op        Operator we want to do
     */
    void onplaceOperation(const Matrix& other, const Operator& op);

    /**
     * Execute the operation on a new matrix
     *
     * @param other     Other matrix to make the operation
     * @param op        Operator we want to do
     * @return Pointer on the result matrix
     */
    Matrix* operation(const Matrix& other, const Operator& op) const;

    /**
     * Execute the operation et get the new data
     *
     * @param other     Other matrix to make the operation
     * @param op        Operator we want to do
     * @return Result data of the operation
     */
    size_t** computeData(const Matrix& other, const Operator& op) const;

    /**
     * Free the data of the current matrix
     */
    void free();
};
