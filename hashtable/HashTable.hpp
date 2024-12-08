#pragma once

template<typename Key, typename Value>
class HashTable {
public:
    virtual void insert(const Key& key, const Value& value) = 0;
    virtual void remove(const Key& key) = 0;
    virtual void clear() = 0;
    virtual bool is_contains(const Key& key) const = 0;
    virtual void load_to_file(const string& path) const = 0;
    
    // Lvalue
    virtual Value& operator[](const Key& key) = 0;
    // Rvalue
    virtual Value operator[](const Key& key) const  = 0;

protected:
    size_t my_hash(const Key& key, size_t capacity) const {
        size_t hash = 17;
        for (const char c : key) { 
            hash = hash * 23 + 3 * c + 4; 
        }
        return hash % capacity;
    }
};
