#ifndef TOKENSTREAM_HPP
#define TOKENSTREAM_HPP

#include "Token.hpp"
#include "TokenFactory.hpp"
#include <istream>
#include <queue>
#include <unordered_set>

class TokenStream
{
public:
    TokenStream(std::istream& _stream);

    const Token& get();

    void putBack(const Token& token);

private:
    void readThroughComments();

    void readLineComment();

    void readMultiLineComment();

    std::string readName();

private:
    std::istream& stream;

    std::queue<Token> buffer;

    std::unordered_set<char> specialSymbols;

    TokenFactory factory;
};

#endif // TOKENSTREAM_HPP
