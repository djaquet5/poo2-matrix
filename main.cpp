#include <iostream>
#include "Matrix.hpp"

using namespace std;

int main(int argc, const char* argv[]) {
    if(argc != 6)
        throw runtime_error("You have to give 5 arguments to the program");

    char *ptr;      // To get the string part of the arguments
    auto modulo = (size_t) strtol(argv[5], &ptr, 10);


    cout << "The modulo is " << modulo << endl << endl;

    Matrix one = Matrix((size_t) strtol(argv[1], &ptr, 10), (size_t) strtol(argv[2], &ptr, 10), modulo);
    Matrix two = Matrix((size_t) strtol(argv[3], &ptr, 10), (size_t) strtol(argv[4], &ptr, 10), modulo);

    cout << "one" << endl
         << one   << endl;

    cout << "two" << endl
         << two   << endl;

    cout << "----------------------------" << endl << endl;

    cout << "one + two (pointer)"  << endl
         << *(one.add(two)) << endl << endl;

    cout << "one - two (pointer)"  << endl
         << *(one.sub(two)) << endl << endl;

    cout << "tow - one (pointer)"  << endl
         << *(two.sub(one)) << endl << endl;

    cout << "one * two (pointer)"  << endl
         << *(one.mult(two)) << endl << endl;

    cout << "----------------------------" << endl << endl;

    cout << "one + two (value)"  << endl
         << one.addAndGetValue(two) << endl << endl;

    cout << "one - two (value)"  << endl
         << one.subAndGetValue(two) << endl << endl;

    cout << "one * two (value)"  << endl
         << one.multAndGetValue(two) << endl << endl;

    cout << "----------------------------" << endl << endl;

    one.addOnThis(two);
    cout << "one + two (on one)"  << endl
         << one << endl << endl;

    one.subOnThis(two);
    cout << "one - two (on one)"  << endl
         << one << endl << endl;

    one.multOnthis(two);
    cout << "one * two (on one)"  << endl
         << one << endl << endl;

    // TODO test copy, test invalid params, etc...

    return EXIT_SUCCESS;
}