#pragma once
#include <vector>
#include "constants.hpp"
#include "HashTable.hpp"
using namespace std;

template<typename Key, typename Value>
struct ItemV2 {
    Key key{};
    Value value{};
    bool is_used = false;

    bool operator== (const ItemV2<Key, Value>& other) const {
        return key == other.key && value == other.value && is_used == other.is_used;
    }
};

template<typename Key, typename Value>
class HashTableV2 final : public HashTable<Key, Value> {
public:
    HashTableV2() : size(0), data(START_CAPACITY) {
        static_assert(is_output_streamable<Key>::value,
        "Key не может быть выведен в поток!\n");
        static_assert(is_output_streamable<Value>::value,
        "Value не может быть выведен в поток!\n");
    };

    HashTableV2(HashTableV2& other) = default;
    ~HashTableV2() = default;
    
    HashTableV2(const string& path) : HashTableV2<Key, Value>() {
        ifstream file(path);
        Key key;
        Value value;
        while (file >> key >> value) {
            insert(key, value);
        }
        file.close();
    }

    void insert(const Key& key, const Value& value) override {
        if (size * 100 / data.size() > REALLOC_FACTOR) {
            resize_data();
        }
        size_t first_index = this->my_hash(key, data.size());
        for (auto i = 0; i < data.size(); ++i) {
            auto index = (first_index + i) % data.size();
            if (data[index].is_used) {
                continue;
            }
            data[index].key = key;
            data[index].value = value;
            data[index].is_used = true;
            ++size;
            return;
        }
    }
    
    void remove(const Key& key) override {
        size_t first_index = this->my_hash(key, data.size());
        for (auto i = 0; i < data.size(); ++i) {
            auto index = (first_index + i) % data.size();
            if (key != data[index].key) {
                continue;
            }
            data[index].is_used = false;
            --size;
            break; 
        }
    }

    void clear() override {
        vector<ItemV2<Key, Value>> cleared_data(START_CAPACITY);
        data = move(cleared_data);
        size = 0;
    }

    bool is_contains(const Key& key) const override {
        size_t first_index = this->my_hash(key, data.size());
        for (auto i = 0; i < data.size(); ++i) {
            auto index = (first_index + i) % data.size();
            if (!data[index].is_used) {
                continue;
            }
            if (key == data[index].key) {
                return true;
            }
        }
        return false;
    }

    void load_to_file(const string& path) const override {
        ofstream file(path);
        for (auto index = 0; index < data.size(); ++index) {
            if (data[index].is_used) {
                file << data[index].key << " " << data[index].value << "\n";     
            }
        }
        file.close();
    }

    size_t get_size() const {
        return size;
    }

    bool is_empty() const {
        return size == 0;
    }


    bool operator==(const HashTableV2<Key, Value>& other) const {
        return data == other.data;   
    }

    bool operator!=(const HashTableV2<Key, Value>& other) const {
        return data != other.data;   
    }

    // Lvalue
    Value& operator[](const Key& key) override {
        if (size * 100 / data.size() > REALLOC_FACTOR) {
            resize_data();
        }
        size_t first_index = this->my_hash(key, data.size());
        for (auto i = 0; i < data.size(); ++i) {
            auto index = (first_index + i) % data.size();
            if (data[index].is_used) {
                if (data[index].key == key) {
                    first_index = index;
                    break;
                } else {
                    continue;
                }
            } else {
                first_index = index;
                insert(key, Value());
                break;
            }
        }
        return data[first_index].value;
    }

    // Rvalue
    Value operator[](const Key& key) const override {
        size_t first_index = this->my_hash(key, data.size());
        
        for (auto i = 0; i < data.size(); ++i) {
            auto index = (first_index + i) % data.size();
            if (data[index].is_used && data[index].key == key) {
                return data[index].value;
            }
        }
        throw runtime_error("Key not found");
    }

    HashTableV2<Key, Value> operator&&(const HashTableV2<Key, Value>& other) const {
        HashTableV2<Key, Value> result;
        for (auto index = 0; index < data.size(); ++index) {
            auto current = data[index];  
            if (current.is_used
                && other.is_contains(current.key)
                && current.value == other[current.key]) {
                    result.insert(current.key, current.value);
                }
        }
        return result;
    }
 
private:
    size_t size;
    vector<ItemV2<Key, Value>> data;    
    
    void resize_data() {
        size_t new_capacity = data.size() * 2;
        vector<ItemV2<Key, Value>> new_data(new_capacity);
        for (const auto& item : data) {
            if (!item.is_used) {
                continue;
            }
            size_t first_index = this->my_hash(item.key, new_capacity);
            for (auto i = 0; i < new_capacity; ++i) {
                auto index = (first_index + i) % data.size();
                if (!new_data[index].is_used) {
                    new_data[index].key = item.key;
                    new_data[index].value = item.value;
                    new_data[index].is_used = true;
                }
            }
        }
        data = move(new_data);
    }
};
