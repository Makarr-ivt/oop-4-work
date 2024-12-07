#pragma once
#include <string>
#include <vector>
#include "constants.hpp"
#include "is_convertible.hpp"
using namespace std;
/* TODO:
- HashTableV1(const string& path, const string& sep=" : ") {};
- void load_to_file(const string& path, const string& sep) const;
- Value& operator[](const Key& key); // lvalue
- Value operator[](const Key& key) const; // rvalue
- тесты
- вторую хэш-таблицу
- cli
*/

template<typename Key, typename Value>
struct ElementV1 {
    Key key{};
    Value value{};
    bool is_used = false;
    ElementV1 *next = nullptr;
};

template<typename Key, typename Value>
class HashTableV1 final {
public:

    HashTableV1() : size(0), data(START_CAPACITY) {
        // Проверяем, можно ли вывести Key и Value в поток
        static_assert(is_output_streamable<Key>::value,
        "Key не может быть выведен в поток.");
        static_assert(is_output_streamable<Value>::value,
        "Value не может быть выведен в поток.");
    }

    HashTableV1(HashTableV1& other) = default;
    HashTableV1(const string& path, const string& sep=" : ") {};
    ~HashTableV1() = default;

    void insert(const Key& key, const Value& value) {
        if (size * 100 / data.size() > REALLOC_FACTOR) {
            resize_data();
        }
        size_t index = my_hash(key, data.size());
        if (!data[index].is_used) {
            data[index].key = key;
            data[index].value = value;
            data[index].is_used = true;
            ++size;
            return;
        }
        // Если ячейка занята, пробуем найти свободное место в цепочке
        ElementV1<Key, Value>* current = &data[index];
        while (current->next != nullptr) {
            // Если ключ уже существует в цепочке, обновляем значение
            if (current->key == key) {
                current->value = value;
                return;
            }
            current = current->next;
        }
        // В конце цепочки нет элемента с данным ключом, добавляем новый
        current->next = new ElementV1<Key, Value>{key, value, true, nullptr};
        ++size;
    }

    void remove(const Key& key) {
        size_t index = my_hash(key, data.size());
        for (auto i = 0; i < data.size(); ++i) {
            if (key != data[index + i].key) {
                continue;
            }
            data[index + i].is_used = false;
            break; 
        }
    }

    void clear() {
        vector<ElementV1<Key, Value>> cleared_data(START_CAPACITY);
        data = move(cleared_data);
        size = 0;
    }

    size_t get_size() const {
        return size;
    }

    bool is_contains(const Key& key) const {
        size_t index = my_hash(key, data.size());
        for (auto i = 0; i < data.size(); ++i) {
            if (!data[index + i].is_used) {
                continue;
            }
            if (key == data[index + i].key) {
                return true;
            }
        }
        return false;
    }
    
    bool is_empty() const {
        return size == 0;
    }

    void load_to_file(const string& path, const string& sep) const;

    Value& operator[](const Key& key) { // lvalue

    }

    Value operator[](const Key& key) const { // rvalue
    
    }

    bool operator==(const HashTableV1& other) const {
        return data == other.data;   
    }

    HashTableV1 operator&&(const HashTableV1& other) const;

private:
    size_t size;
    vector<ElementV1<Key, Value>> data;    
    
    void resize_data() {
        size_t new_capacity = data.size() * 2;
        vector<ElementV1<Key, Value>> new_data(new_capacity);
        for (const auto& element : data) {
            if (!element.is_used) {
                continue;
            }
            size_t index = my_hash(element.key, new_capacity);
            for (auto i = 0; i < new_capacity; ++i) {
                if (!new_data[index + i].is_used) {
                    new_data[index + i].key = element.key;
                    new_data[index + i].value = element.value;
                    new_data[index + i].is_used = true;
                }
            }
        }
        data = move(new_data);
    }

    size_t my_hash(const Key& key, size_t capacity) const {
        size_t hash = 17;
        for (const char c : key) { 
            hash = hash * 23 + 3 * c + 4; 
        }
        return hash % capacity;
    }
};
