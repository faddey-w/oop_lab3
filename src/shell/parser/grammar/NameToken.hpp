#include "../tokenization.h"


class NameToken: public Token {
    std::string name = "";
public:
    std::string get_type() const {return "name";}

protected:
    void _parse(std::string, unsigned &offset);
    bool _equals(const Token*) const;
};


void NameToken::_parse(std::string, unsigned &offset) {

}
