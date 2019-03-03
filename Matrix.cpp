#include "Matrix.hpp"
#include "Add.hpp"

Matrix::Matrix(size_t n, size_t m, size_t modulo) {
    if(modulo == 0 || n == 0 || m == 0) {
        throw std::invalid_argument("Invalid parameters\n");
    }

    auto data = new size_t*[n];
    for(size_t i = 0; i < n; ++i) {
        data[i] = new size_t[m];
    }

    for(size_t i = 0; i < n; ++i) {
        for(size_t j = 0; j < m; ++j) {
            data[i][j] = rand() % modulo;
        }
    }

    this->n = n;
    this->m = m;
    this->modulo = modulo;
    this->data = data;
}

Matrix::Matrix(size_t n, size_t m, size_t modulo, size_t **data) {
    if(modulo <= 0 || n == 0 || m == 0 || data == nullptr) {
        throw std::invalid_argument("Invalid parameters\n");
    }

    for(size_t i = 0; i < n; i++) {
        for(size_t j = 0; j < m; j++) {
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

size_t** Matrix::operation(size_t** target, const Matrix& other, const Operator& op) {
    if(modulo != other.modulo) {
        throw std::invalid_argument("The modulo of the Matrices must be the same\n");
    }

    size_t maxN = std::max(n, other.n);
    size_t maxM = std::max(m, other.m);
    size_t minN = std::min(n, other.n);
    size_t minM = std::min(m, other.m);

    if(target != nullptr) {
        free();
    }

    target = new size_t*[maxN];
    for(size_t i = 0; i < maxN; i++) {
        target[i] = new size_t[maxM];
    }

    for(size_t i = 0; i < maxN; i++) {
        for(size_t j = 0; j < maxM; j++) {
            if(i < minN && j < minM) {
                target[i][j] = op.apply(data[i][j], other.data[i][j]) % modulo;
            } else {
                target[i][j] = 0;
            }
        }
    }
    return target;

}

void Matrix::free() {
    for(size_t i = 0; i < n; ++i) {
        delete(data[i]);
    }

    delete(data);
}

std::ostream& operator<<(std::ostream& ostream, const Matrix& matrix) {

    for(size_t i = 0; i < matrix.n; ++i) {
        for(size_t j = 0; j < matrix.m; ++j)
            ostream << matrix.data[i][j] << " ";

        ostream << std::endl;
    }

    return ostream;
}

size_t Matrix::at(size_t i, size_t j) const {
    if(i >= n || j >= m) {
        throw std::runtime_error("Invalid index\n");
    }

    return data[i][j];
}

// Operations
// Returns pointer on result Matrix
Matrix* Matrix::add(const Matrix& other) {
    Matrix* result;
    size_t** newData = nullptr;
    Add op = Add();

    operation(newData, other, op);

    result = new Matrix(std::max(this->n, other.n),std::max(this->m, other.m), modulo, newData);

    return result;
}

Matrix* Matrix::sub(const Matrix& other) {

}

Matrix* Matrix::mult(const Matrix& other) {

}

// Returns new Matrix (by value)
Matrix Matrix::addAndGetValue(const Matrix& other) const {

}

Matrix Matrix::subAndGetValue(const Matrix& other) const {

}

Matrix Matrix::multAndGetValue(const Matrix& other) const {

}

// Modifies this Matrix
void Matrix::addOnThis(Matrix& other) {

}

void Matrix::subOnThis(Matrix& other) {

}

void Matrix::multOnthis(Matrix& other) {

}