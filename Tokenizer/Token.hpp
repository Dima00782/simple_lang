#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>

class Token {
public:
    enum Type
    {
        PLUS,
        MINUS,
        ASTERISK,
        SLASH,
        DEGREE,
        EQUALITY,
        SEMICOLON,
        ROUND_OPEN_BRACKET,
        ROUND_CLOSE_BRACKET,
        FIGURE_OPEN_BRACKET,
        FIGURE_CLOSE_BRACKET,
        VOID,
        DOUBLE,
        INT,
        NUMBER_DOUBLE,
        NUMBER_INT,
        NAME,
        RETURN,
        PRINT,
        WHILE,
        IF,
        ELSE,
        MORE,
        LESS,
        COMMA,
        END_STREAM,
    };

public:
    Token(Type _type, const std::string& _value);

public:
    Type type;

    std::string value;
};

#endif // TOKEN_HPP
