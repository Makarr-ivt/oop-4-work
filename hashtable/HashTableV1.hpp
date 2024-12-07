#pragma once

template<typename Key, typename Value>
struct ElementV1 {
    Key key;
    Value value;
    ElementV2 *next = nullptr;
};

template<typename Key, typename Value>
class HashTableV1 final {
public:
private:
};