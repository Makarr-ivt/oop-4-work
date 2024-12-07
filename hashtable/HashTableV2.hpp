#pragma once

template<typename Key, typename Value>
struct ElementV2 {
    Key key;
    Value value;
    bool is_deleted = false;
};

template<typename Key, typename Value>
class HashTableV2 final {
public:
private:
};