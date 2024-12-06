#include "tests.hpp"
#include "ui_functions.hpp"
#include <iostream>
#include <string>
using namespace std;


int main() {
    if (run_all_tests() != 0) {
        return 1;
    }
    
    return 0;
}