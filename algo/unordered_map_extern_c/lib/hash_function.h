#ifndef __hash_function_h
#define __hash_function_h

#include <stddef.h>

struct hash_function {
    static size_t hash(const void *ptr, size_t len, 
            size_t seed = static_cast<size_t>(0xc70f6907UL))
    {   
        const char *first = static_cast<const char *>(ptr);
        const char *last = first+len;
        for ( ; first != last; ++first) {
            seed ^= (size_t) *first + 0x9e3779b9 + (seed << 6) + (seed >> 2); 
        }   
        return seed;
    }   

    template<typename T>
    static size_t hash(const T &val)
    {   
        return hash(&val, sizeof(val));
    }   

    template<typename T>
    static size_t hash_combine(const T &val, size_t seed) 
    {   
        return hash(&val, sizeof(val), seed); 
    }   
};

#endif
