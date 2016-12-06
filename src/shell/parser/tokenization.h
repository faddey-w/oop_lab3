#ifndef LAB3_TOKENS_HPP
#define LAB3_TOKENS_HPP

#include <string>
#include <vector>
#include <exception>
#include <memory>


class SyntaxError: public std::runtime_error {
public:
    SyntaxError(const std::string &s): std::runtime_error(s) {}
    SyntaxError(): SyntaxError("") {}
};


class Token {
public:

    typedef std::shared_ptr<Token> Ptr;

    // Creates new Token instance and yields ownership over it to user code
    template<typename ConcreteToken>
    static Token* try_parse(const std::string &str, int &offset) {
        ConcreteToken *token = new ConcreteToken;
        try {
            offset = token->parse(str);
            if (offset < 0) {
                throw SyntaxError();
            }
            return token;
        } catch (SyntaxError &err) {
            delete token;
            return nullptr;
        }
    }

    // Comparisons - suitable for testing
    bool operator==(const Token &other) const {
        if (get_type() != other.get_type()) {
            return false;
        }
        return _equals(&other);
    }
    bool operator!=(const Token &other) const {
        return !(*this == other);
    }

    // Returned string should be the same for all instances of same class
    virtual const std::string& get_type() const = 0;

    // Parses beginning of given string.
    // Fills token details according to parsed string.
    // Returns number of characters occupied by this token.
    // Throws SyntaxError if parsing fails.
    virtual int parse(const std::string&) = 0;

    virtual ~Token() {}

protected:
    virtual bool _equals(const Token*) const = 0;
};


// Creates a sequence of tokens and yields ownership over it
// Throws SyntaxError if there are unknown syntax token;
std::vector<std::shared_ptr<Token> > tokenize(const std::string &str);


#endif //LAB3_TOKENS_HPP
