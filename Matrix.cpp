#include "Matrix.hpp"
#include "Add.hpp"
#include "Sub.hpp"
#include "Mult.hpp"

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

Matrix::Matrix(size_t n, size_t m, size_t modulo, size_t** data) {
    if(modulo == 0 || n == 0 || m == 0) {
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

size_t** Matrix::computeData(const Matrix &other, const Operator &op) const {
    if(modulo != other.modulo) {
        throw std::invalid_argument("The modulo of the Matrices must be the same\n");
    }

    const Matrix* minN;
    const Matrix* maxN;
    const Matrix* minM;
    const Matrix* maxM;

    if(n <= other.n) {
        minN = this;
        maxN = &other;
    } else {
        minN = &other;
        maxN = this;
    }

    if(m <= other.m) {
        minM = this;
        maxM = &other;
    } else {
        minM = &other;
        maxM = this;
    }

    auto newData = new size_t*[maxN->n];
    for(size_t i = 0; i < maxN->n; i++) {
        newData[i] = new size_t[maxM->m];
    }

    for(size_t i = 0; i < maxN->n; i++) {
        for(size_t j = 0; j < maxM->m; j++) {
            if(i < minN->n) {
                if(j < minM->m) {
                    newData[i][j] = op.apply(data[i][j], other.data[i][j], modulo);
                } else {
                    newData[i][j] = maxM->data[i][j];
                }
            } else {
                if(j < minM->m) {
                    newData[i][j] = maxN->data[i][j];
                } else {
                    newData[i][j] = 0;
                }
            }
        }
    }

    return newData;
}

void Matrix::onplaceOperation(const Matrix& other, const Operator& op) {
    this->data = computeData(other, op);
    this->n = std::max(n, other.n);
    this->m = std::max(m, other.m);
}

Matrix* Matrix::operation(const Matrix& other, const Operator& op) const {
    size_t** newData = computeData(other, op);

    return new Matrix(std::max(n, other.n), std::max(m, other.m), modulo, newData);
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

// Operations
// Returns pointer on result Matrix
Matrix* Matrix::add(const Matrix& other) const {
    Add op = Add();
    return operation(other, op);
}

Matrix* Matrix::sub(const Matrix& other) const {
    Sub op = Sub();
    return operation(other, op);
}

Matrix* Matrix::mult(const Matrix& other) const {
    Mult op = Mult();
    return operation(other, op);
}

// Returns new Matrix (by value)
Matrix Matrix::addAndGetValue(const Matrix& other) const {
    return *add(other);
}

Matrix Matrix::subAndGetValue(const Matrix& other) const {
    return *sub(other);
}

Matrix Matrix::multAndGetValue(const Matrix& other) const {
    return *mult(other);
}

// Modifies this Matrix
void Matrix::addOnThis(Matrix& other) {
    Add op = Add();
    onplaceOperation(other, op);
}

void Matrix::subOnThis(Matrix& other) {
    Sub op = Sub();
    onplaceOperation(other, op);
}

void Matrix::multOnthis(Matrix& other) {
    Mult op = Mult();
    onplaceOperation(other, op);
}