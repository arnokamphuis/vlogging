#ifndef __RND_H__
#define __RND_H__

#include <random>
#include <cassert>

template<typename T>
std::vector<T> RND(std::size_t min, std::size_t max, std::size_t count) {
    assert(false);
}

template<>
std::vector<int> RND(std::size_t min, std::size_t max, std::size_t count) {
    std::vector<int> v;
    v.reserve(count);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);
    for (std::size_t i = 0; i<count; ++i) 
        v.push_back(dis(gen));
    return v;
}

#endif // __RND_H__