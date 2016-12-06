#ifndef LAB3_NAMETOKEN_HPP
#define LAB3_NAMETOKEN_HPP

#include "../tokenization.h"


class NameToken: public Token {
    std::string name = "";
public:

    NameToken(): NameToken("") {};
    NameToken(const std::string& s): name(s) {};

    const std::string& get_type() const {
        static const std::string type_name("name");
        return type_name;
    }

    const std::string& get_name() const { return name; }

    int parse(const std::string&) {
        return -1;
    }
protected:
    bool _equals(const Token*) const {
        return false;
    }
};


#endif // LAB3_NAMETOKEN_HPP
