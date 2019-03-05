#include "Matrix.hpp"
#include "Add.hpp"
#include "Sub.hpp"
#include "Mult.hpp"

Matrix::Matrix(size_t nbLines, size_t nbColumns, size_t modulo) {
    if(modulo == 0 || nbLines == 0 || nbColumns == 0) {
        throw std::invalid_argument("Invalid parameters\n");
    }

    size_t** data = new size_t*[nbLines];
    for(size_t i = 0; i < nbLines; ++i) {
        data[i] = new size_t[nbColumns];
    }

    // TODO : check rand
    for(size_t i = 0; i < nbLines; ++i) {
        for(size_t j = 0; j < nbColumns; ++j) {
//            data[i][j] = (size_t) (1 + rand() / (RAND_MAX + 1.) * (modulo - 1));
            data[i][j] = rand() % modulo;
        }
    }

    this->nbLines = nbLines;
    this->nbColumns = nbColumns;
    this->modulo = modulo;
    this->data = data;
}

Matrix::Matrix(size_t nbLines, size_t nbColumns, size_t modulo, size_t** data) {
    if(modulo == 0 || nbLines == 0 || nbColumns == 0) {
        throw std::invalid_argument("Invalid parameters\n");
    }

    for(size_t i = 0; i < nbLines; i++) {
        for(size_t j = 0; j < nbColumns; j++) {
            if(data[i][j] < 0 || data[i][j] >= modulo) {
                throw std::invalid_argument("Invalid input table\n");
            }
        }
    }

    this->nbLines = nbLines;
    this->nbColumns = nbColumns;
    this->modulo = modulo;
    this->data = data;
}

Matrix::Matrix(const Matrix &other) {
    size_t** dataCopy = new size_t*[other.nbLines];

    for(size_t i = 0; i < other.nbLines; ++i) {
        dataCopy[i] = new size_t[other.nbColumns];
    }

    for(size_t i = 0; i < other.nbLines; ++i) {
        for(size_t j = 0; j < other.nbColumns; ++j) {
            dataCopy[i][j] = other.data[i][j];
        }
    }

    this->nbLines = other.nbLines;
    this->nbColumns = other.nbColumns;
    this->modulo = other.modulo;
    this->data = dataCopy;

}

size_t** Matrix::computeData(const Matrix &other, const Operator &op) const {
    if(modulo != other.modulo) {
        throw std::invalid_argument("The modulo of the Matrices must have the same modulo\n");
    }

    const Matrix* minN;
    const Matrix* maxN;
    const Matrix* minM;
    const Matrix* maxM;

    if(nbLines <= other.nbLines) {
        minN = this;
        maxN = &other;
    } else {
        minN = &other;
        maxN = this;
    }

    if(nbColumns <= other.nbColumns) {
        minM = this;
        maxM = &other;
    } else {
        minM = &other;
        maxM = this;
    }

    size_t** newData = new size_t*[maxN->nbLines];
    for(size_t i = 0; i < maxN->nbLines; i++) {
        newData[i] = new size_t[maxM->nbColumns];
    }

    for(size_t i = 0; i < maxN->nbLines; i++) {
        for(size_t j = 0; j < maxM->nbColumns; j++) {
            if(i < minN->nbLines) {
                if(j < minM->nbColumns) {
                    newData[i][j] = op.apply(data[i][j], other.data[i][j], modulo);
                } else {
                    newData[i][j] = maxM->data[i][j];
                }
            } else {
                if(j < minM->nbColumns) {
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
    // Free the data to avoid memory leak
    free();

    this->data = computeData(other, op);
    this->nbLines = std::max(nbLines, other.nbLines);
    this->nbColumns = std::max(nbColumns, other.nbColumns);
}

Matrix* Matrix::operation(const Matrix& other, const Operator& op) const {
    size_t** newData = computeData(other, op);

    return new Matrix(std::max(nbLines, other.nbLines), std::max(nbColumns, other.nbColumns), modulo, newData);
}

void Matrix::free() {
    for(size_t i = 0; i < nbLines; ++i) {
        delete(data[i]);
    }

    delete(data);
}

std::ostream& operator<<(std::ostream& ostream, const Matrix& matrix) {
    for(size_t i = 0; i < matrix.nbLines; ++i) {
        for(size_t j = 0; j < matrix.nbColumns; ++j)
            ostream << matrix.data[i][j] << " ";

        ostream << std::endl;
    }

    return ostream;
}

// Operations
// Returns pointer on result Matrix
Matrix* Matrix::add(const Matrix& other) const {
//    Add op = Add();
    return operation(other, Add());
}

Matrix* Matrix::sub(const Matrix& other) const {
//    Sub op = Sub();
    return operation(other, Sub());
}

Matrix* Matrix::mult(const Matrix& other) const {
//    Mult op = Mult();
    return operation(other, Mult());
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
//    Add op = Add();
    onplaceOperation(other, Add());
}

void Matrix::subOnThis(Matrix& other) {
//    Sub op = Sub();
    onplaceOperation(other, Sub());
}

void Matrix::multOnthis(Matrix& other) {
//    Mult op = Mult();
    onplaceOperation(other, Mult());
}