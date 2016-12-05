#include "../tokenization.h"



class AssignmentToken: public Token {
    std::string var_name;
public:

    AssignmentToken(): AssignmentToken("") {};
    AssignmentToken(const std::string& s): var_name(s) {};

    int parse(const std::string&);

    const std::string& get_type() const {
        static const std::string type_name("assignment");
        return type_name;
    }

    const std::string& get_var_name() const {
        return var_name;
    }
protected:
    bool _equals(const Token*) const;
};


int AssignmentToken::parse(const std::string&) {
    return -1;
}


bool AssignmentToken::_equals(const Token *) const {
    return false;
}
