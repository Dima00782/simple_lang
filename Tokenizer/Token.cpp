#include "Token.hpp"

Token::Token(Type _type, const std::string& _value)
    : type(_type)
    , value(_value)
{
}
