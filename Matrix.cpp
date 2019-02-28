#include "Matrix.hpp"

Matrix::Matrix(size_t n, size_t m, size_t modulo) {
    if(modulo <= 0) {
        throw std::invalid_argument("The modulo must be a positive integer\n");
    }

    auto data = new size_t*[n];
    for(size_t i = 0; i < n; ++i) {
        data[i] = new size_t[m];
    }

    for(size_t i = 0; i < n; ++i) {
        for(size_t j = 0; j < m; ++j) {
            data[i][j] = rand() / (RAND_MAX) * (n - 1);
        }
    }

    this->n = n;
    this->m = m;
    this->modulo = modulo;
    this->data = data;
}

Matrix::Matrix(size_t n, size_t m, size_t modulo, size_t **data) {
    if(modulo <= 0) {
        throw std::invalid_argument("The modulo must be a positive integer\n");
    }

    for(size_t i = 0; i < n; ++i) {
        for(size_t j = 0; j < m; ++j) {
            if(data[i][j] < 0 || data[i][j] >= modulo) {
                throw std::invalid_argument("Invalid input table\n");
            }
        }
    }

    this->n = n;
    this->m = m;
    this->modulo = modulo;
    this->data = data;
}

Matrix::Matrix(const Matrix &other) {
    auto dataCopy = new size_t*[other.n];
    for(size_t i = 0; i < other.n; ++i) {
        dataCopy[i] = new size_t[other.m];
    }

    for(size_t i = 0; i < other.n; ++i) {
        for(size_t j = 0; j < other.m; ++j) {
            dataCopy[i][j] = other.data[i][j];
        }
    }

    this->n = other.n;
    this->m = other.m;
    this->modulo = other.modulo;
    this->data = dataCopy;

}

void Matrix::free() {
    for(size_t i = 0; i < n; ++i) {
        delete(data[i]);
    }

    delete(data);
}

std::ostream& operator<<(std::ostream ostream, const Matrix& matrix) {

    for(size_t i = 0; i < matrix.n; ++i) {
        ostream << '[';
        for(size_t j = 0; j < matrix.m; ++j) {
            ostream << matrix.data[i][j];
        }
        ostream << ']' << std::endl;
    }
}

size_t Matrix::at(size_t i, size_t j) const {
    if(i >= n || j >= m) {
        throw std::runtime_error("Invalid index\n");
    }

    return data[i][j];
}