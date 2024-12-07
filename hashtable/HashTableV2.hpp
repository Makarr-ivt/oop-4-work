#pragma once
#include <vector>
#include "constants.hpp"
using namespace std;

template<typename Key, typename Value>
struct ElementV2 {
    Key key{};
    Value value{};
    bool is_used = false;
};

template<typename Key, typename Value>
class HashTableV2 final {
public:
    HashTableV2() 
        : size(0),
        data(START_CAPACITY) {};
    HashTableV2(HashTableV2& other) = default;
    ~HashTableV2() = default;
    HashTableV2(const string& path, const string& sep=" : ") {};
    
    void insert(const Key& key, const Value& value) {
        if (size * 100 / data.size() > REALLOC_FACTOR) {
            resize_data();
        }
        size_t index = my_hash(key, data.size());
        for (auto i = 0; i < data.size(); ++i) {
            if (data[index + i].is_used) {
                continue;
            }
            data[index + i].key = key;
            data[index + i].value = value;
            data[index + i].is_used = true;
            ++size;
            return;
        }
    }
    
    bool remove(const Key& key);

    void clear();
    size_t get_size() const;
    bool is_contains(const Key& key) const;
    bool is_empty() const;
    void load_to_file(const string& path, const string& sep) const;

    Value& operator[](const Key& key);
    bool operator<<(const HashTableV2& other) const;
    HashTableV2 operator&&(const HashTableV2& other) const;
private:
    size_t size;
    vector<ElementV2<Key, Value>> data;    
    bool resize_data();
};
