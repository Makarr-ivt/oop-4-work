#pragma once
#include "HashTableV1.hpp"
#include "HashTableV2.hpp"
#include <cassert>
#include <iostream>
using namespace std;


template<typename T> // template for HashTable V1 or V2
int test_default_constructor() {
    T example;
    assert(example.get_size() == 0
    && "default constructor creates wrong start size!\n");
    assert(example.is_empty() == true
    && "created constructor is not empty!");
    return 0;
}

template<typename T> // template for HashTable V1 or V2
int test_copy_constructor() {
    T ht; 
    ht.insert("first key", "first value"); // да, по факту я тестирую только вариант {string : string}
    ht.insert("second", "");
    ht.insert("third", "something else");
    T ht2(ht);
    assert(ht == ht2 // here i also test operator==
    && "copied hashtable must be equal to original!");

    ht2.remove("second");
    assert(ht != ht2 // here i also test operator!=
    && "change in copy must not modify original!");

    ht.clear();
    assert(ht != ht2 // here i also test operator!=
    && "change in original must not modify copy!");
    return 0;
}

template<typename T> // template for HashTable V1 or V2
int test_change_in_size() {
    T ht;
    ht.insert("1", "11");
    assert(ht.get_size() == 1
    && "size must be 1 here!");

    ht.insert("2", "22");
    ht.insert("3", "33");
    assert(ht.get_size() == 3
    && "size must be 3 here!");

    ht.remove("2");
    assert(ht.get_size() == 2
    && "size must be 2 here!");

    ht.clear();
    assert(ht.get_size() == 0
    && "size must be 0 here!");
    
    assert(ht.is_empty() == true
    && "hashtable must be empty after clearing!");
    
    return 0;
}

template<typename T> // template for HashTable V1 or V2
int test_file_data_exchange() {
    T ht1("D:/oop_4_work_final/unit_tests/test1.txt");
    assert(ht1.get_size() == 5
    && "ht1 must contain 5 items!");
    assert(ht1["k2"] == "v2");
    assert(ht1.is_contains("k5"));
    return 0;
}

template<typename T> // template for HashTable V1 or V2
int test_intersection() {
    T ht1("D:/oop_4_work_final/unit_tests/test1.txt");
    T ht2("D:/oop_4_work_final/unit_tests/test2.txt");
    T ht3 = ht1 && ht2;
    assert(ht3.get_size() == 2);
    assert(ht3.is_contains("k2"));
    assert(ht3["k3"] == "v3");
    assert(!ht3.is_contains("k4"));
    return 0;
}


template<typename T> // template for HashTable V1 or V2
int run_all_tests() {
    int fails_counter = 0;
    fails_counter += test_default_constructor<T>();
    fails_counter += test_copy_constructor<T>();
    fails_counter += test_change_in_size<T>();
    fails_counter += test_intersection<T>();
    fails_counter += test_file_data_exchange<T>();
    cout << fails_counter << " tests were failed!\n";
    return fails_counter;
}