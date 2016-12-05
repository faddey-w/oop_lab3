#include "../tokenization.h"


class NameToken: public Token {
    std::string name = "";
public:
    const std::string& get_type() const {
        static const std::string type_name("name");
        return type_name;
    }

    int parse(const std::string&);
protected:
    bool _equals(const Token*) const;
};


int NameToken::parse(const std::string&) {
    return -1;
}


bool NameToken::_equals(const Token *) const {
    return false;
}
