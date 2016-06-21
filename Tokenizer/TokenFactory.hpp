#ifndef TOKENFACTORY_HPP
#define TOKENFACTORY_HPP

#include "Token.hpp"
#include <string>
#include <unordered_map>
#include <memory>

class TokenFactory
{
public:
    TokenFactory();

    const Token& create(const std::string& name);

private:
    typedef std::unique_ptr<const Token> Ptr;

    std::unordered_map< std::string, std::unique_ptr<const Token> > tokens;
};

#endif // TOKENFACTORY_HPP
