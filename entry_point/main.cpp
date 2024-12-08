#include "tests.hpp"
#include "ui_functions.hpp"
#include <iostream>
#include <string>
using namespace std;
#include "HashTableV1.hpp"


int main() {
    if (run_all_tests<HashTableV2<string, string>>() != 0) {
        return 1;
    }

    return 0;
}