#include <string>
#include <iostream>
#include "Operator.hpp"

#ifndef MATRIX_HPP
#define MATRIX_HPP

class Matrix {
private:
    size_t n;
    size_t m;
    size_t modulo;

    size_t** data;

public:
    // Constructor (random)
    Matrix(size_t n, size_t m, size_t modulo);

    // Constructor (from data)
    Matrix(size_t n, size_t m, size_t modulo, size_t** data);

    // copy
    Matrix(const Matrix& other);

    // Get n
    size_t getN() const {
        return n;
    }
    // Get m
    size_t getM() const {
        return m;
    }
    // Get modulo
    size_t getModulo() const {
        return modulo;
    }
    // get elem
    size_t at(size_t i, size_t j) const;
    // Destructor
    virtual ~Matrix() {
        free();
    }

    // << operator overload
    friend std::ostream& operator<<(std::ostream& ostream, const Matrix& matrix);

    // Operations
    // Returns pointer on result Matrix
    Matrix* add(const Matrix& other) const;
    Matrix* sub(const Matrix& other) const;
    Matrix* mult(const Matrix& other) const;

    // Returns new Matrix (by value)
    Matrix addAndGetValue(const Matrix& other) const;
    Matrix subAndGetValue(const Matrix& other) const;
    Matrix multAndGetValue(const Matrix& other) const;

    // Modifies other Matrix
    void addOn(Matrix& other);
    void subOn(Matrix& other);
    void multOn(Matrix& other);

private:
    // Matrix operation with Operator op
    Matrix* operation(Matrix& other, Operator op);

    // free
    void free();
};

#endif // MATRIX_HPP
