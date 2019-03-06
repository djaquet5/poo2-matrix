/*
 -----------------------------------------------------------------------------------
 Laboratoire : 01
 Fichier     : Matrix.cpp
 Auteur(s)   : David Jaquet & Christoph Rueff
 Date        : 06.03.2019

 But         : Implémentation de la classe Matrix

 Remarque(s) :

 -----------------------------------------------------------------------------------
*/

#include <ctime>
#include "Matrix.hpp"
#include "Add.hpp"
#include "Sub.hpp"
#include "Mult.hpp"

// Constructor without data
Matrix::Matrix(size_t nbLines, size_t nbColumns, size_t modulo) {
    static bool isRandOn = false;

    if(modulo == 0 || nbLines == 0 || nbColumns == 0) {
        throw std::invalid_argument("Invalid parameters\n");
    }

    size_t** data;

    try {
        data = new size_t*[nbLines];

        for(size_t i = 0; i < nbLines; ++i) {
            data[i] = new size_t[nbColumns];
        }
    } catch (std::bad_array_new_length& e) {
        throw std::invalid_argument("Invalid parameters, matrix is to big");
    }

    // Initialize random seed only once
    if(!isRandOn){
        srand(time(NULL));
        isRandOn = true;
    }

    for(size_t i = 0; i < nbLines; ++i) {
        for(size_t j = 0; j < nbColumns; ++j) {
            data[i][j] = (size_t) (1 + rand() / (RAND_MAX + 1.) * (modulo - 1));
        }
    }

    this->nbLines = nbLines;
    this->nbColumns = nbColumns;
    this->modulo = modulo;
    this->data = data;
}

// Constructor with data
Matrix::Matrix(size_t nbLines, size_t nbColumns, size_t modulo, size_t** data) {
    if(modulo <= 0 || nbLines <= 0 || nbColumns <= 0 || data == nullptr) {
        throw std::invalid_argument("Invalid parameters\n");
    }

    // Check the data given
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

// Copy constructor
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

// Compute a new matrix data depending on the operation given
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

// Change the current matrix with the result of the operation
void Matrix::onplaceOperation(const Matrix& other, const Operator& op) {
    size_t** newData = computeData(other, op);

    // Free the data to avoid memory leak
    free();

    this->data = newData;
    this->nbLines = std::max(nbLines, other.nbLines);
    this->nbColumns = std::max(nbColumns, other.nbColumns);
}

// Get the result of the operation
Matrix* Matrix::operation(const Matrix& other, const Operator& op) const {
    return new Matrix(std::max(nbLines, other.nbLines), std::max(nbColumns, other.nbColumns),
                      modulo, computeData(other, op));
}

// Free the data of the matrix
void Matrix::free() {
    for(size_t i = 0; i < nbLines; ++i) {
        delete(data[i]);
    }

    delete(data);
}

// Overload of the << operator
std::ostream& operator << (std::ostream& ostream, const Matrix& matrix) {
    for(size_t i = 0; i < matrix.nbLines; ++i) {
        for(size_t j = 0; j < matrix.nbColumns; ++j)
            ostream << matrix.data[i][j] << " ";

        ostream << std::endl;
    }

    return ostream;
}

/**************************** Operations ****************************/

// Returns pointer on result Matrix
Matrix* Matrix::add(const Matrix& other) const {
    return operation(other, Add());
}

Matrix* Matrix::sub(const Matrix& other) const {
    return operation(other, Sub());
}

Matrix* Matrix::mult(const Matrix& other) const {
    return operation(other, Mult());
}

// Returns new Matrix
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
Matrix Matrix::addOnThis(Matrix& other) {
    onplaceOperation(other, Add());

    return *this;
}

Matrix Matrix::subOnThis(Matrix& other) {
    onplaceOperation(other, Sub());

    return *this;
}

Matrix Matrix::multOnthis(Matrix& other) {
    onplaceOperation(other, Mult());

    return *this;
}