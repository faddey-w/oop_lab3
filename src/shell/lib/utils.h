#ifndef LAB3_UTILS_H
#define LAB3_UTILS_H

#include <iostream>
#include <vector>
#include <memory>
#include <map>


template<typename T> using dict = std::map<std::string, T>;


template<typename T>
dict<T> merge_dicts(const dict<T> &m1, const dict<T> &m2) {
    dict<T> result(m1);
    for(auto &item : m2) {
        result[item.first] = item.second;
    }
    return result;
};

#endif //LAB3_UTILS_H
