#include "TokenFactory.hpp"
#include <cassert>
#include <sstream>
#include <cmath>

TokenFactory::TokenFactory()
{
    tokens.emplace("+", std::move(Ptr (new Token(Token::PLUS, "0"))));
    tokens.emplace("-", std::move(Ptr (new Token(Token::MINUS, "0"))));
    tokens.emplace("*", std::move(Ptr (new Token(Token::ASTERISK, "0"))));
    tokens.emplace("/", std::move(Ptr (new Token(Token::SLASH, "0"))));
    tokens.emplace("^", std::move(Ptr (new Token(Token::DEGREE, "0"))));
    tokens.emplace("=", std::move(Ptr (new Token(Token::EQUALITY, "0"))));
    tokens.emplace(";", std::move(Ptr (new Token(Token::SEMICOLON, "0"))));
    tokens.emplace("(", std::move(Ptr (new Token(Token::ROUND_OPEN_BRACKET, "0"))));
    tokens.emplace(")", std::move(Ptr (new Token(Token::ROUND_CLOSE_BRACKET, "0"))));
    tokens.emplace("{", std::move(Ptr (new Token(Token::FIGURE_OPEN_BRACKET, "0"))));
    tokens.emplace("}", std::move(Ptr (new Token(Token::FIGURE_CLOSE_BRACKET, "0"))));
    tokens.emplace("void", std::move(Ptr (new Token(Token::VOID, "0"))));
    tokens.emplace("int", std::move(Ptr (new Token(Token::INT, "0"))));
    tokens.emplace("double", std::move(Ptr (new Token(Token::DOUBLE, "0"))));
    tokens.emplace("return", std::move(Ptr (new Token(Token::RETURN, "0"))));
    tokens.emplace("print", std::move(Ptr (new Token(Token::PRINT, "0"))));
    tokens.emplace("while", std::move(Ptr (new Token(Token::WHILE, "0"))));
    tokens.emplace("if", std::move(Ptr (new Token(Token::IF, "0"))));
    tokens.emplace("else", std::move(Ptr (new Token(Token::ELSE, "0"))));
    tokens.emplace(">", std::move(Ptr (new Token(Token::MORE, "0"))));
    tokens.emplace("<", std::move(Ptr (new Token(Token::LESS, "0"))));
    tokens.emplace(",", std::move(Ptr (new Token(Token::COMMA, "0"))));
    tokens.emplace("", std::move(Ptr (new Token(Token::END_STREAM, "0"))));
}

const Token& TokenFactory::create(const std::string& name)
{
    if (tokens.find(name) == tokens.end())
    {
        double value = -1;
        std::stringstream ss(name);
        if (ss >> value)
        {
            if (0 == (value - floor(value)))
            {
                tokens.emplace(name, std::move(Ptr (new Token(Token::NUMBER_INT, name))));
            }
            else
            {
                tokens.emplace(name, std::move(Ptr (new Token(Token::NUMBER_DOUBLE, name))));
            }
        }
        else if (std::isalpha(name[0]))
        {
            tokens.emplace(name, std::move(Ptr (new Token(Token::NAME, name))));
        }
        else
        {
            throw std::logic_error("invalid token");
        }
    }

    return *tokens.find(name)->second;
}
