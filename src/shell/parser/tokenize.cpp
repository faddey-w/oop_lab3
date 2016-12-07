
#include "tokenization.h"
#include "tokens/meta.hpp"


std::vector<std::shared_ptr<Token> > tokenize(const std::string &orig_str) {
    std::string str(orig_str);
    std::vector<std::shared_ptr<Token> > tokens;
    while (str.size() > 0) {
        str.erase(0, str.find_first_not_of(" \n\r\t"));
        Token *tok = nullptr;
        for(auto meta: TokenMeta::objects) {
            int offset = -1;
            tok = meta->try_parse(str, offset);
            if (tok == nullptr) continue;
            str.erase(0, (unsigned)offset);
            tokens.push_back(std::shared_ptr<Token>(tok));
            break;
        }
        if (tok == nullptr) {
            throw SyntaxError("unknown syntax: " + str.substr(0, 10));
        }
    }
    return tokens;
}
