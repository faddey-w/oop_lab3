#ifndef LAB3_ASSIGNMENTTOKEN_HPP
#define LAB3_ASSIGNMENTTOKEN_HPP

#include "../tokenization.h"


class AssignmentToken: public Token {
    std::string var_name;
public:

    AssignmentToken(): AssignmentToken("") {};
    AssignmentToken(const std::string& s): var_name(s) {};

    const std::string& get_type() const {
        static const std::string type_name("assignment");
        return type_name;
    }

    const std::string& get_var_name() const {
        return var_name;
    }

    int parse(const std::string& str){
        int name_start = -1;
        bool name_done = false;
        std::string buf;
        for(int idx = 0; idx < str.size(); idx++) {
            char ch = str[idx];
            if (std::isalnum(ch) || ch == '_') {
                if (name_start == -1 && std::isdigit(ch)) {
                    return -1; // name can't start with a digit
                }
                if (name_done) return -1; // name parsing done but there is letter again
                if (name_start == -1) name_start = idx;
            } else if (name_start == -1) {
                if (!std::isspace(ch)) return -1;
            } else {
                if (!name_done) {
                    name_done = true;
                    buf = str.substr(name_start, idx - name_start);
                }
                if (ch == '=') {
                    var_name = buf;
                    return idx+1;
                } else if (!std::isspace(ch)) {
                    return -1;
                }
            }
        }
        return -1;
    }
protected:
    bool _equals(const Token* t) const {
        const auto other = Token::try_convert<AssignmentToken>(t);
        if (!other) return false;
        return var_name == other->var_name;
    }
};


#endif // LAB3_ASSIGNMENTTOKEN_HPP
