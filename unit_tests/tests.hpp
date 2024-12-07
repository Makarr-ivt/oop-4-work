#pragma once
#include <cassert>
#include "HashTableV1.hpp"
#include <iostream>
using namespace std;


template<typename T> // Hashtable V1 or V2
int test_default_constructor() {
    return 0;
}

template<typename T> // Hashtable V1 or V2
int test_copy_constructor() {
    return 0;
}

template<typename T> // Hashtable V1 or V2
int test_change_in_size() {
    return 0;
}

template<typename T> // Hashtable V1 or V2
int test_add_operator() {
    return 0;
}

template<typename T> // Hashtable V1 or V2
int test_equality_operator() {
    return 0;
}

template<typename T> // Hashtable V1 or V2
int test_intersection() {
    return 0;
}

template<typename T> // Hashtable V1 or V2
int test_file_data_exchange() {
    return 0;
}

template<typename T> // Hashtable V1 or V2
int run_all_tests() {
    int fails_counter = 0;
    fails_counter += test_default_constructor<T>();
    fails_counter += test_copy_constructor<T>();
    fails_counter += test_change_in_size<T>();
    fails_counter += test_add_operator<T>();
    fails_counter += test_equality_operator<T>();
    fails_counter += test_intersection<T>();
    fails_counter += test_file_data_exchange<T>();
    cout << fails_counter << " tests were failed!\n";
    return fails_counter;
}