#pragma once
#include <string>
#include <vector>
#include <fstream>
#include "constants.hpp"
#include "is_convertible.hpp"
using namespace std;


template<typename Key, typename Value>
struct ElementV1 {
    Key key{};
    Value value{};
    bool is_used = false;
    ElementV1<Key, Value> *next = nullptr;

    bool operator== (const ElementV1& other) const {
        return key == other.key && value == other.value && is_used == other.is_used;
    }
};

template<typename Key, typename Value>
class HashTableV1 final {
public:

    HashTableV1() : size(0), data(START_CAPACITY) {
        // Проверяем, можно ли вывести Key и Value в поток
        static_assert(is_output_streamable<Key>::value,
        "Key не может быть выведен в поток!\n");
        static_assert(is_output_streamable<Value>::value,
        "Value не может быть выведен в поток!\n");
    }

    HashTableV1(HashTableV1& other) = default;

    HashTableV1(const string& path) : HashTableV1<Key, Value>() {
        ifstream file(path);
        Key key;
        Value value;
        while (file >> key >> value) {
            insert(key, value);
        }
        file.close();
    }

    ~HashTableV1() = default;

    void insert(const Key& key, const Value& value) {
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
                current->is_used = true;
                ++size;
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
            --size;
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
        const ElementV1<Key, Value>* current = &data[index];
        if (current->key == key && current->is_used) {
            return true;
        }
        while (current->next != nullptr) {
            current = current->next;
            if (current->is_used && current->key == key) {
                return true;
            }
        }
        return false;
    }
    
    bool is_empty() const {
        return size == 0;
    }

    void load_to_file(const string& path) const {
        ofstream file(path);
        for (auto index = 0; index < data.size(); ++index) {
            const ElementV1<Key, Value>* current = &data[index];
            if (current->is_used) {
                file << current->key << " " << current->value << "\n";    
            }
            while (current->next != nullptr) {   
                current = current->next;
                if (current->is_used) {
                    file << current->key << " " << current->value << "\n";    
                }
            } 
        }
        file.close();
    }

    // Lvalue
    Value& operator[](const Key& key) {
        size_t index = my_hash(key, data.size()); // Получаем индекс

        // Ищем элемент в корзине
        ElementV1<Key, Value>* current = &data[index]; // Предполагаем, что первый элемент в этой корзине

        // Перебираем цепочку элементов
        while (current != nullptr) {
            if (current->is_used && current->key == key) {
                // Если ключ найден, возвращаем ссылку на его значение
                return current->value;
            }
            current = current->next;
        }

        // Если ключ не найден, используем метод insert для добавления нового элемента
        insert(key, Value());
        // Снова ищем вновь добавленный элемент (поиск начинается с того же индекса)
        current = &data[index]; // Обновляем указатель на начало цепочки
        do {
            if (current->is_used && current->key == key) {
                // Возвращаем ссылку на значение нового элемента
                return current->value;
            }
            current = current->next;
        } while (current != nullptr);
    }

    // Rvalue
    Value operator[](const Key& key) const {
        size_t index = my_hash(key, data.size());
        const ElementV1<Key, Value>* current = &data[index];

        while (current != nullptr) {
            if (current->is_used && current->key == key) {
                return current->value;
            }
            current = current->next;
        }
        return Value(); // Возвращаем значение по умолчанию, если ключ не найден
    }

    bool operator==(const HashTableV1& other) const {
        return data == other.data;   
    }

    bool operator!=(const HashTableV1& other) const {
        return data != other.data;   
    }

    HashTableV1<Key, Value> operator&&(const HashTableV1<Key, Value>& other) const {
        HashTableV1<Key, Value> result;
        for (auto index = 0; index < data.size(); ++index) {
            const ElementV1<Key, Value>* current = &data[index];        
            while (current != nullptr) {
                if (current->is_used
                && other.is_contains(current->key)
                && current->value == other[current->key]) {
                    result.insert(current->key, current->value);
                }
                current = current->next; // Переход к следующему элементу
            }
        }
        return result;
    }


    void print() {
        cout << "{\n";
        for (auto index = 0; index < data.size(); ++index) {
            const ElementV1<Key, Value>* current = &data[index];
            if (current->is_used) {
                cout <<"\t'"<< current->key << "' : '" << current->value << "'\n";    
            }
            while (current->next != nullptr) {   
                current = current->next;
                if (current->is_used) {
                    cout <<"\t'"<< current->key << "' : '" << current->value << "'\n";    
                }
            } 
        }
        cout << "}\n";
    }

private:
    size_t size;
    vector<ElementV1<Key, Value>> data;    
    
    size_t my_hash(const Key& key, size_t capacity) const {
        size_t hash = 17;
        for (const char c : key) { 
            hash = hash * 23 + 3 * c + 4; 
        }
        return hash % capacity;
    }
};
