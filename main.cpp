#include <iostream>

using namespace std;

int main(int argc, char** argv) {
    for (int i = 1; i < argc; i++) {
        string arg(argv[i]);
        if (arg == "-p" || arg == "--parallel") {
            cout << "Running program with multiple threads" << endl;
        } else if (arg == "-f") {

        } else {
            cerr << "ERROR: Unknown command line argument: " << arg << endl;
            return 1;
        }
    }
    return 0;
}
