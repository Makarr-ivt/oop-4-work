#pragma once
#include <vector>
#include "constants.hpp"
using namespace std;

template<typename Key, typename Value>
struct ElementV2 {
    Key key{};
    Value value{};
    bool is_deleted = false;
};

template<typename Key, typename Value>
class HashTableV2 final {
public:
    HashTableV1() 
        : size(0),
        data(START_CAPACITY) {};
    HashTableV1(HashTableV1& other) = default;
    ~HashTableV1() = default;
    HashTableV1(const string& path, const string& sep=" : ") {};
    
    void insert(const Key& key, const Value& value);
    bool remove(const Key& key);

    void clear();
    size_t get_size() const;
    bool is_contains(const Key& key) const;
    bool is_empty() const;
    void load_to_file(const string& path, const string& sep) const;

    Value& operator[](const Key& key);
    bool operator<<(const HashTableV1& other) const;
    HashTableV1 operator&&(const HashTableV1& other) const;
private:
    size_t size;
    vector<ElementV2<Key, Value>> data;    
    bool resize_data();
};
