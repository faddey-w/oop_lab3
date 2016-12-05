#include "../tokenization.h"


class BraceToken: public Token {
    bool is_open = true;
public:
    const std::string& get_type() const {
        static const std::string type_name("brace");
        return type_name;
    }

    int parse(const std::string&);
protected:
    bool _equals(const Token*) const;
};


int BraceToken::parse(const std::string&) {
    return -1;
}


bool BraceToken::_equals(const Token *) const {
    return false;
}

