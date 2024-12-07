#include "tests.hpp"
#include "ui_functions.hpp"
#include <iostream>
#include <string>
using namespace std;
#include "HashTableV1.hpp"

int main() {
    if (run_all_tests<HashTableV1<string, int>>() != 0) {
        return 1;
    }
    HashTableV1<string, int> ht;
    ht.insert("first", 3);
    ht.insert("second", 14);
    ht.insert("third", 3);
    cout << ht.get_size() << endl;
    cout << ht.is_contains("first") << endl;
    cout << ht.is_empty() << endl;
    HashTableV1<string, int> ht2(ht);
    ht.clear();
    cout << ht.is_contains("first") << endl;
    cout << ht.is_empty() << endl;
    cout << ht2.is_contains("first") << endl;
    ht2.remove("first");
    cout << ht2.is_contains("first") << endl;
    cout << ht2.is_empty() << endl;

    return 0;
}