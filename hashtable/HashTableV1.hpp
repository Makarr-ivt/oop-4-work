#pragma once
#include <string>
#include <vector>
#include "constants.hpp"
using namespace std;


template<typename Key, typename Value>
struct ElementV1 {
    Key key{};
    Value value{};
    ElementV2 *next = nullptr;
};

template<typename Key, typename Value>
class HashTableV1 final {
public:
    HashTableV1() {};
    HashTableV1(HashTableV1& OldHashTable) {};
    HashTableV1(const string& path, const string& sep=" : ") {};
    ~HashTableV1() = default;

    void insert(const Key& key, const Value& value);
    bool remove(const Key& key);

    void clear();
    size_t get_size() const;
    bool is_contains(const Key& key) const;
    bool is_empty() const;
    void load_to_file(const string& path, const string& sep) const;

    Value& operator[](const Key& key);
    bool operator==(const HashTableV1& other) const;
    HashTableV1 operator&&(const HashTableV1& other) const;

private:
    size_t size;
    vector<ElementV1<Key, Value>> data;    
    void resize_data(size_t new_capacity)

    size_t myHash(const Key& key, size_t capacity) const {
        size_t hash = 0;
        for (char c : key) {
            hash = hash * 37 + c; 
        }
        return hash % tableSize;
    }
};
