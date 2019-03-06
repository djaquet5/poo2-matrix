/*
 -----------------------------------------------------------------------------------
 Laboratoire : 01
 Fichier     : main.cpp
 Auteur(s)   : David Jaquet & Christoph Rueff
 Date        : 06.03.2019

 But         : Programme de tests pour des calculs de matrices

 Remarque(s) : - Les matrices sont de tailles variables
               - Les valeurs au sein de la matrices sont comprises entre
                 0 et un modulo fourni
               - Les tailles ainsi que le modulo sont fournis en paramètre
               - Les opérations implémentées sont l'addition, la soustraction,
                 et la multiplication.
               - La fonction test() n'est pas appelée afin de garder l'affichage
                 demandé dans la consigne du laboratoire

 -----------------------------------------------------------------------------------
*/

#include <iostream>
#include "Matrix.hpp"

using namespace std;

/**
 * Fonction de tests personnalisés
 */
void test(Matrix& one, Matrix& two, size_t modulo){

    cout << "/************************* Test function *************************/" << endl;

    cout << "one" << endl
         << one   << endl;

    cout << "two" << endl
         << two   << endl;

    // Check the operators who give the pointer to a new matrix
    cout << "one + two (pointer)"  << endl
         << *(one.add(two)) << endl;

    cout << "one - two (pointer)"  << endl
         << *(one.sub(two)) << endl;

    cout << "two - one (pointer)"  << endl
         << *(two.sub(one)) << endl;

    cout << "one * two (pointer)"  << endl
         << *(one.mult(two)) << endl;

    cout << "----------------------------" << endl << endl;

    // Check the operators who change the value of the matrix
    one.addOnThis(two);
    cout << "one + two (on one)"  << endl
         << one << endl;

    one.subOnThis(two);
    cout << "one - two (on one)"  << endl
         << one << endl;

    one.multOnthis(two);
    cout << "one * two (on one)"  << endl
         << one << endl;

    cout << "----------------------------" << endl << endl;

    // Check the copy constructor
    Matrix three = Matrix(one);
    cout << "three (copy of one)" << endl
         << three << endl;

    // Change the value of the copied matrix
    one.addOnThis(one);
    cout << "one after one = one + one" << endl
         << one << endl;

    // Check if the matrix hasn't change
    cout << "three (copy of one), to check if it has changed" << endl
         << three << endl;

    cout << "----------------------------" << endl << endl;

    // Check the constructor with invalid parameters
    try{
        Matrix matrix = Matrix(0, 3, modulo);
        cout << "Matrice creee" << endl
             << "Test echoue" << endl;
    } catch (invalid_argument& e) {
        cout << "Impossible de creer une matrice avec 0 ligne" << endl
             << "Test reussi" << endl;
    }

    try{
        Matrix matrix = Matrix(-1, 3, modulo);
        cout << "Matrice creee" << endl
             << "Test echoue" << endl;
    } catch (invalid_argument& e) {
        cout << "Impossible de creer une matrice avec trop de lignes" << endl
             << "Test reussi" << endl;
    }

    try{
        Matrix matrix = Matrix(3, 0, modulo);
        cout << "Matrice creee" << endl
             << "Test echoue" << endl;
    } catch (invalid_argument& e) {
        cout << "Impossible de creer une matrice avec 0 colonne" << endl
             << "Test reussi" << endl;
    }

    try{
        Matrix matrix = Matrix(3, -1, modulo);
        cout << "Matrice creee" << endl
             << "Test echoue" << endl;
    } catch (invalid_argument& e) {
        cout << "Impossible de creer une matrice avec trop de colonnes" << endl
             << "Test reussi" << endl;
    }

    // Check an operation with matrix who has different modulos
    Matrix four = Matrix(3, 3, 10);

    try{
        one.addOnThis(four);
        cout << one << endl
             << "On peut faire une addition entre 2 matrices avec 2 modulos different" << endl
             << "Test echoue" << endl;
    } catch(invalid_argument& e) {
        cout << e.what()
             << "Test reussi" << endl;
    }

    // Check constructor with a null pointer instead of datas
    try{
        Matrix five = Matrix(3, 3, 5, nullptr);
    } catch(invalid_argument& e) {
        cout << e.what()
             << "Test reussi" << endl;
    }
}

/**
 * Programme de test
 *
 * @param argc  Nombre d'argument passé au programme
 * @param argv  Arguments passés au programme
 * @return Valeur de fin du programme
 */
int main(int argc, const char* argv[]) {
    if(argc != 6)
        throw runtime_error("You have to give 5 arguments to the program");

    // To get the string part of the arguments
    char *ptr;

    size_t modulo = (size_t) strtol(argv[5], &ptr, 10);


    cout << "The modulo is " << modulo << endl << endl;

    Matrix one = Matrix((size_t) strtol(argv[1], &ptr, 10), (size_t) strtol(argv[2], &ptr, 10), modulo);
    Matrix two = Matrix((size_t) strtol(argv[3], &ptr, 10), (size_t) strtol(argv[4], &ptr, 10), modulo);

    cout << "one" << endl
         << one   << endl;

    cout << "two" << endl
         << two   << endl;

    // Check the operators who give a new matrix
    cout << "one + two"  << endl
         << one.addAndGetValue(two) << endl;

    cout << "one - two"  << endl
         << one.subAndGetValue(two) << endl;

    cout << "one * two"  << endl
         << one.multAndGetValue(two) << endl;

    test(one, two, modulo);

    return EXIT_SUCCESS;
}