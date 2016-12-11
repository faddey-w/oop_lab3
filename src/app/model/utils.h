#ifndef LAB3_APP_UTILS_H
#define LAB3_APP_UTILS_H

#include <memory>
#include <string>

typedef std::shared_ptr<std::string> str_ptr;
typedef std::shared_ptr<int> int_ptr;


template<typename T>
str_ptr mk_string(const T &arg) {
    return std::make_shared<std::string>(arg);
}

inline int_ptr mk_int(int x) {
    return std::make_shared<int>(x);
}

#endif //LAB3_APP_UTILS_H
