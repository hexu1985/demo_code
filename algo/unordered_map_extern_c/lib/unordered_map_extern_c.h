#ifndef __unordered_map_extern_c_h
#define __unordered_map_extern_c_h

#include <stddef.h>

struct unordered_map_s;
typedef struct unordered_map_s unordered_map_t;

typedef struct unordered_map_key_s {
    const void *key;        // 指向key所在内存的指针, key指向的内存由调用者维护
    size_t len;             // key的长度
} unordered_map_key_t;

typedef void *unordered_map_value_t;    // value的内存由调用者维护

#ifdef __cplusplus
extern "C" {
#endif

// 如果两个key相等, 返回1, 其他返回0
typedef int equal_func(const unordered_map_key_t *, const unordered_map_key_t *);

typedef size_t hash_func(const unordered_map_key_t *);

// 创建一个unordered_map
unordered_map_t *unordered_map_create(size_t n);

// 释放一个unordered_map
void unordered_map_destroy(unordered_map_t *map);

// 向hash表里插入一项
// 如果成功, 返回1,
// 如果已经存在相同key的项, 返回0
int unordered_map_insert(unordered_map_t *map, const unordered_map_key_t *key, unordered_map_value_t val);

// 从hash表里查找一项
// 如果找到符合的项, 返回1,
// 如果没有符合的项, 返回0
int unordered_map_find(unordered_map_t *map, const unordered_map_key_t *key, unordered_map_value_t *val);

// 从hash表里删除一项
// 返回被删除的项的个数
int unordered_map_delete(unordered_map_t *map, const unordered_map_key_t *key);

// 遍历hash表中的每一项,
// 并对每一项调用foreach_func
typedef void foreach_func(const unordered_map_key_t *, unordered_map_value_t);
void unordered_map_foreach(unordered_map_t *map, foreach_func *func);

#ifdef __cplusplus
}   // extern "C" {
#endif

#endif

