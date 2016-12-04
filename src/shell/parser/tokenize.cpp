
#include "tokenization.h"
#include "grammar/meta.hpp"


std::vector<Token*> tokenize(std::string str) {
    std::vector<Token*> tokens;
    while (str.size() > 0) {
        str.erase(0, s.find_first_not_of(" \n\r\t")+1);
        for(auto meta: TokenMeta::objects) {
            unsigned offset = -1;
            Token *tok = meta->try_parse(str, offset);
            if (tok == nullptr) continue;
            str.erase(0, offset);
            tokens.push_back(tok);
        }
        if (tok == nullptr) {
            throw SyntaxError("unknown syntax: " + str.substr(0, 10));
        }
    }
    return tokens;
}
