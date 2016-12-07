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

    int parse(const std::string& str) {
        size_t name_start = str.find_first_not_of(" \t\n");
        if (str.size() <= name_start) return -1;
        if (!std::isalpha(str[name_start])) return -1;
        size_t idx = name_start+1;
        for(; idx < str.size(); ++idx) {
            char ch = str[idx];
            if (!std::isalnum(ch) && ch != '_') {
                break;
            }
        }
        name = str.substr(name_start, idx - name_start);
        return int(idx);
    }
protected:
    bool _equals(const Token* t) const {
        const auto other = Token::try_convert<NameToken>(t);
        if (!other) return false;
        return name == other->name;
    }
};


#endif // LAB3_NAMETOKEN_HPP
