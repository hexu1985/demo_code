#include "unordered_map_extern_c.h"
#include "hash_function.h"
#include <cstring>
#include <utility>
#include <unordered_map>

namespace {

inline 
int default_equal_func(const unordered_map_key_t *key1, const unordered_map_key_t *key2)
{
    size_t len = std::min(key1->len, key2->len);
    return memcmp(key1->key, key2->key, len) == 0 && key1->len == key2->len;
}

struct key_equal {
    equal_func *equal_to;

    key_equal(): equal_to(default_equal_func) {}
    key_equal(equal_func *f): equal_to(f) {}

    bool operator ()(const unordered_map_key_t &key1, const unordered_map_key_t &key2) const
    {
        return equal_to(&key1, &key2);
    }
};

inline
size_t default_hash_func(const unordered_map_key_t *key)
{
    return hash_function::hash((void *) key->key, key->len);
}

struct hasher {
    hash_func *hash;

    hasher(): hash(default_hash_func) {}
    hasher(hash_func *f): hash(f) {}

    size_t operator ()(const unordered_map_key_t &key) const
    {
        return hash(&key);
    }
};

}   // namespace {

struct unordered_map_s {
    std::unordered_map<unordered_map_key_t, unordered_map_value_t, hasher, key_equal> map;

    explicit unordered_map_s(size_t n): map(n) {}
};

unordered_map_t *unordered_map_create(size_t n)
{
    return new unordered_map_s(n);
}

void unordered_map_destroy(unordered_map_t *map)
{
    delete map;
}

int unordered_map_insert(unordered_map_t *map, const unordered_map_key_t *key, unordered_map_value_t val)
{
    auto ret = map->map.emplace(*key, val);
    return ret.second;
}

int unordered_map_find(unordered_map_t *map, const unordered_map_key_t *key, unordered_map_value_t *val)
{
    auto iter = map->map.find(*key);
    if (iter == map->map.end()) {
        return 0;
    }

    if (val) {
        *val = iter->second;
    }

    return 1;
}

int unordered_map_delete(unordered_map_t *map, const unordered_map_key_t *key)
{
    return map->map.erase(*key);
}

void unordered_map_foreach(unordered_map_t *map, foreach_func *func)
{
    for (auto &item : map->map) {
        func(&item.first, item.second);
    }
}

