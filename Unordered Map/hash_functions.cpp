#include "hash_functions.h"

size_t polynomial_rolling_hash::operator() (std::string const & str) const {
    /* TODO */
    size_t hash = 0;
    size_t p = 1;
    size_t b = 19; 
    auto m = 3298534883309ul;

    for(size_t i = 0; i < str.size(); i++){
        char letter = str[i]; 
        hash += (letter * p);
        p = (p * b) % m;
    }
    return hash; 
}

size_t fnv1a_hash::operator() (std::string const & str) const {
    /* TODO */
    auto basis = 0xCBF29CE484222325; 
    auto prime = 0x00000100000001B3;
    size_t hash = basis;
    for(size_t i = 0; i < str.size(); i++){
        hash =  (hash ^ str[i]);
        hash = hash * prime;
    }
    return hash;
}
