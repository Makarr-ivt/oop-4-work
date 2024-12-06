#include "tests.hpp"
#include <iostream>
using namespace std;

int run_all_tests() {
    int fails_counter = 0;
    fails_counter += test_default_constructor();
    fails_counter += test_copy_constructor();
    fails_counter += test_change_in_size();
    fails_counter += test_add_operator();
    fails_counter += test_intersection();
    fails_counter += test_file_data_exchange();
    cout << fails_counter << " tests were failed!\n";
    return fails_counter;
}

int test_default_constructor() {
    return 0;
}

int test_copy_constructor() {
    return 0;
}

int test_change_in_size() {
    return 0;
}

int test_add_operator() {
    return 0;
}

int test_intersection() {
    return 0;
}

int test_file_data_exchange() {
    return 0;
}
