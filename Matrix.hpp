#include <string>
#include <iostream>
#include "Operator.hpp"

#ifndef MATRIX_HPP
#define MATRIX_HPP

class Matrix {
private:
    size_t nbLines;
    size_t nbColumns;
    size_t modulo;

    size_t** data;

public:
    // Constructor (random)
    Matrix(size_t nbLines, size_t nbColumns, size_t modulo);

    // Constructor (from data)
    Matrix(size_t nbLines, size_t nbColumns, size_t modulo, size_t** data);

    // copy
    Matrix(const Matrix& other);

    // Destructor
    virtual ~Matrix() {
        free();
    }

    // << operator overload
    friend std::ostream& operator << (std::ostream& ostream, const Matrix& matrix);

    // Operations
    // Returns pointer on result Matrix
    Matrix* add(const Matrix& other) const;
    Matrix* sub(const Matrix& other) const;
    Matrix* mult(const Matrix& other) const;

    // Returns new Matrix (by value)
    Matrix addAndGetValue(const Matrix& other) const;
    Matrix subAndGetValue(const Matrix& other) const;
    Matrix multAndGetValue(const Matrix& other) const;

    // Modifies this Matrix
    void addOnThis(Matrix& other);
    void subOnThis(Matrix& other);
    void multOnthis(Matrix& other);

private:
    // Operation on this
    void onplaceOperation(const Matrix& other, const Operator& op);

    // Operation on new Matrix
    Matrix* operation(const Matrix& other, const Operator& op) const;

    // Compute and return new data
    size_t** computeData(const Matrix& other, const Operator& op) const;

    // free
    void free();
};

#endif // MATRIX_HPP
