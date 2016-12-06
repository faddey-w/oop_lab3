#include "../tokenization.h"


class ParenthesisToken: public Token {
    bool _is_open = true;
public:

    ParenthesisToken() : ParenthesisToken(true) {}
    ParenthesisToken(bool is_open): _is_open(is_open) {}

    const std::string& get_type() const {
        static const std::string type_name("brace");
        return type_name;
    }

    bool is_open() { return _is_open; }

    int parse(const std::string&);
protected:
    bool _equals(const Token*) const;
};


int ParenthesisToken::parse(const std::string&) {
    return -1;
}


bool ParenthesisToken::_equals(const Token *) const {
    return false;
}
