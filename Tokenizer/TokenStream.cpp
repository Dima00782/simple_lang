#include "TokenStream.hpp"
#include <string>
#include <sstream>

TokenStream::TokenStream(std::istream& _stream)
    : stream(_stream)
{
    specialSymbols.insert('+');
    specialSymbols.insert('-');
    specialSymbols.insert('*');
    specialSymbols.insert('/');
    specialSymbols.insert('^');
    specialSymbols.insert('=');
    specialSymbols.insert(';');
    specialSymbols.insert('(');
    specialSymbols.insert(')');
    specialSymbols.insert('{');
    specialSymbols.insert('}');
    specialSymbols.insert(',');
    specialSymbols.insert('\0');
}

const Token& TokenStream::get()
{
    if (!buffer.empty())
    {
        const Token& result = buffer.front();
        buffer.pop();
        return result;
    }

    //readThroughComments();

    std::string tokenPresentation;
    char ch = '\0';

    stream >> ch;
    if ('\0' != ch)
    {
        tokenPresentation += ch;
        if (isdigit(ch))
        {
            stream.putback(ch);
            double number = 0;
            stream >> number;
            tokenPresentation = std::to_string(number);
        }
        else if (specialSymbols.find(ch) == specialSymbols.end())
        {
            tokenPresentation += readName();
        }
    }

    return factory.create(tokenPresentation);
}

void TokenStream::putBack(const Token& token)
{
    buffer.push(token);
}

void TokenStream::readThroughComments()
{
    bool inComment = true;
    char symbol = '\0';

    while (inComment && !stream.eof())
    {
        stream >> symbol;
        if ('/' == symbol)
        {
            stream >> symbol;
            if ('/' == symbol)
            {
                readLineComment();
            }
            else if ('*' == symbol)
            {
                readMultiLineComment();
            }
            else
            {
                inComment = false;
            }
        }
        else
        {
            inComment = false;
        }
    }
    stream.putback(symbol);
}

void TokenStream::readLineComment()
{
    char ch;
    stream.get(ch);
    while ('\n' != ch && !stream.eof())
    {
        stream.get(ch);
    }
}

void TokenStream::readMultiLineComment()
{
    bool inComment = true;
    char symbol = '\0';

    while (inComment && !stream.eof())
    {
        stream >> symbol;
        if ('*' == symbol)
        {
            stream >> symbol;
            if ('/' == symbol)
            {
                inComment = false;
            }
        }
    }
}

std::string TokenStream::readName()
{
    std::string name;
    char ch;

    do
    {
        stream.get(ch);
        name += ch;
    }
    while (' ' != ch && specialSymbols.find(ch) == specialSymbols.end() && !stream.eof());

    stream.putback(ch);
    name.pop_back();

    return name;
}
