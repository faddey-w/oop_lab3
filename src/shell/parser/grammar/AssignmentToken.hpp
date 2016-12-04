#include "../tokenization.h"



class AssignmentToken: public Token {
    std::string var_name = "";
public:
    std::string get_type() const {return "assignment";}

protected:
    void _parse(std::string, unsigned &offset);
    bool _equals(const Token*) const;
};


void AssignmentToken::_parse(std::string, unsigned &offset) {

}
