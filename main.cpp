#include <iostream>
#include "Matrix.hpp"

using namespace std;

int main(int argc, const char* argv[]) {
    if(argc != 6)
        throw runtime_error("You have to give 5 arguments to the program");

    char *ptr;      // To get the string part of the arguments
    size_t modulo = (size_t) strtol(argv[5], &ptr, 10);


    cout << "The modulo is " << modulo << endl << endl;

    Matrix one = Matrix((size_t) strtol(argv[1], &ptr, 10), (size_t) strtol(argv[2], &ptr, 10), modulo);
    Matrix two = Matrix((size_t) strtol(argv[3], &ptr, 10), (size_t) strtol(argv[4], &ptr, 10), modulo);

    cout << "one" << endl
         << one   << endl;

    cout << "two" << endl
         << two   << endl;

    cout << "----------------------------" << endl << endl;

    cout << "one + two (pointer)"  << endl
         << *(one.add(two)) << endl;

    cout << "one - two (pointer)"  << endl
         << *(one.sub(two)) << endl;

    cout << "two - one (pointer)"  << endl
         << *(two.sub(one)) << endl;

    cout << "one * two (pointer)"  << endl
         << *(one.mult(two)) << endl;

    cout << "----------------------------" << endl << endl;

    cout << "one + two (value)"  << endl
         << one.addAndGetValue(two) << endl;

    cout << "one - two (value)"  << endl
         << one.subAndGetValue(two) << endl;

    cout << "one * two (value)"  << endl
         << one.multAndGetValue(two) << endl;

    cout << "----------------------------" << endl << endl;

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

    Matrix three = Matrix(one);
    cout << "three (copy of one)" << endl
         << three << endl;

    one.addOnThis(one);
    cout << "one after one = one + one" << endl
         << one << endl;

    cout << "three (copy of one), to check if it has changed" << endl
         << three << endl;


    cout << "----------------------------" << endl << endl;

    try{
        Matrix matrix = Matrix(0, 3, modulo);
        cout << "Matrice creee" << endl
             << "Test echoue" << endl;
    } catch (invalid_argument e) {
        cout << "Impossible de creer une matrice avec 0 ligne" << endl
             << "Test reussi" << endl;
    }

    // TODO: size_t -1 = 18446744073709551615, génère une erreur ?
//    try{
//        Matrix matrix = Matrix(-1, 3, modulo);
//        cout << "Matrice creee" << endl
//             << "Test echoue" << endl;
//    } catch (invalid_argument e) {
//        cout << "Impossible de creer une matrice avec -1 ligne" << endl
//             << "Test reussi" << endl;
//    }

    try{
        Matrix matrix = Matrix(3, 0, modulo);
        cout << "Matrice creee" << endl
             << "Test echoue" << endl;
    } catch (invalid_argument e) {
        cout << "Impossible de creer une matrice avec 0 colonne" << endl
             << "Test reussi" << endl;
    }

//    try{
//        Matrix matrix = Matrix(3, -1, modulo);
//        cout << "Matrice creee" << endl
//             << "Test echoue" << endl;
//    } catch (invalid_argument e) {
//        cout << "Impossible de creer une matrice avec 0 colonne" << endl
//             << "Test reussi" << endl;
//    }
//    cout << sizeof(size_t) << endl << sizeof(long long);

    Matrix four = Matrix(3, 3, 10);

    try{
        one.addOnThis(four);
        cout << one << endl
             << "On peut faire une addition entre 2 matrices avec 2 modulos different" << endl
             << "Test echoue" << endl;
    } catch(invalid_argument e) {
        cout << e.what()
             << "Test reussi" << endl;
    }
    return EXIT_SUCCESS;
}