#include "../tokenization.h"


class BraceToken: public Token {
    bool is_open = true;
public:
    std::string get_type() const {return "brace";}

protected:
    void _parse(std::string, unsigned &offset);
    bool _equals(const Token*) const;
};


void BraceToken::_parse(std::string, unsigned &offset) {

}

