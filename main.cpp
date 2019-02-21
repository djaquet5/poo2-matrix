#include <iostream>

using namespace std;

int main(int argc, const char* argv[]) {
    if(argc != 6)
        throw runtime_error("You have to give 5 arguments to the program");

    size_t modulo = (unsigned int) argv[5];


    cout << "The modulo is " << modulo << endl << endl;

//    Matrix one = Matrix(argv[1], argv[2], modulo);
//    Matrix two = Matrix(argv[3], argv[4], modulo);
//
//    cout << "one" << endl
//         << one   << endl;
//
//    cout << "two" << endl
//         << two   << endl;
//
//    cout << "one + two" << endl;
//
//    cout << "one ? two" << endl;
//
//    cout << "one x two" << endl;
    return EXIT_SUCCESS;
}