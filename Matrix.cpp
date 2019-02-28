#include "Matrix.hpp"

Matrix::Matrix(size_t n, size_t m, size_t modulo) {
    if(modulo <= 0) {
        throw std::invalid_argument("The modulo must be a positive integer\n");
    }

    auto matrix = new size_t*[n];
    for(size_t i = 0; i < n; ++i) {
        matrix[i] = new size_t[m];
    }

    for(size_t i = 0; i < n; ++i) {
        for(size_t j = 0; j < m; ++j) {
            matrix[i][j] = rand() / (RAND_MAX + 1) * n;
        }
    }

    this->n = n;
    this->m = m;
    this->modulo = modulo;
    this->matrix = matrix;
}

Matrix::Matrix(size_t n, size_t m, size_t modulo, size_t **matrix) {
    if(modulo <= 0) {
        throw std::invalid_argument("The modulo must be a positive integer\n");
    }

    for(size_t i = 0; i < n; ++i) {
        for(size_t j = 0; j < m; ++j) {
            if(matrix[i][j] < 0 || matrix[i][j] >= modulo) {
                throw std::invalid_argument("Invalid input table\n");
            }
        }
    }

    this->n = n;
    this->m = m;
    this->modulo = modulo;
    this->matrix = matrix;
}

Matrix::Matrix(const Matrix &other) {

}

size_t Matrix::at(size_t i, size_t j) const {
    if(i >= n || j >= m) {
        throw std::runtime_error("Invalid index\n");
    }
}