#pragma once 

#include <unordered_map>

template <typename K, typename V>
bool contains_key(const std::unordered_map<K, V>& map, const K& key) {
    return map.find(key) != map.end();
}