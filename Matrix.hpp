#include <string>
#include "Operator.hpp"

#ifndef MATRIX_HPP
#define MATRIX_HPP

class Matrix {
private:
    size_t n;
    size_t m;
    size_t modulo;

    size_t** matrix;

public:
    // Constructor
    Matrix(size_t n, size_t m, size_t modulo);
    // copy
    Matrix(const Matrix& other);

    // Destructor
    virtual ~Matrix();

    // change to << operator
    std::string toString() const;

    // Operations
    // Returns pointer on result Matrix
    Matrix* add(const Matrix& other);
    Matrix* sub(const Matrix& other);
    Matrix* mult(const Matrix& other);

    // Returns new Matrix (by value)
    Matrix addAndGetValue(const Matrix& other);
    Matrix subAndGetValue(const Matrix& other);
    Matrix multAndGetValue(const Matrix& other);

    // Modifies other Matrix
    void addOn(Matrix& other);
    void subOn(Matrix& other);
    void multOn(Matrix& other);

private:
    // Matrix operation with Operator op
    Matrix* operation(Matrix& other, Operator op);
};

#endif // MATRIX_HPP
