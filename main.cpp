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

//    cout << "one" << endl
//         << one   << endl;
//
//    cout << "two" << endl
//         << two   << endl;
//
//    cout << "----------------------------" << endl << endl;
//
//    cout << "one + two"  << endl
//         << one.add(two) << endl << endl;
//
//    Matrix three = one.addAndGetValue(two);
//    cout << three << endl << endl;
//
//    Matrix twoCopy = Matrix(two);
//    one.addOn(twoCopy);
//    cout << twoCopy << endl << endl;
//
//    cout << "----------------------------" << endl << endl;
//
//    cout << "two + one (should be the same result than before)" << endl
//         << two.add(one) << endl << endl;
//
//    three = two.addAndGetValue(one);
//    cout << three << endl << endl;
//
//    // Here twoCopy is a copy of the matrix one
//    twoCopy = Matrix(one);
//    two.addOn(twoCopy);
//
//    cout << "----------------------------" << endl << endl;
//
//    cout << twoCopy << endl << endl;
//    cout << "one - two" << endl;
//
//    cout << "one x two" << endl;
    return EXIT_SUCCESS;
}