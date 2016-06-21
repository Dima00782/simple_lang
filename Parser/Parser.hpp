#ifndef PARSER_HPP
#define PARSER_HPP

#include "Tokenizer/Token.hpp"
#include "Tokenizer/TokenStream.hpp"
#include "Nodes/INode.hpp"
#include "Nodes/IFnode.hpp"
#include <memory>
#include <unordered_map>

class Parser
{
public:
    typedef std::shared_ptr<INode> Ptr;

    Parser(TokenStream &_tokenStream);

    Ptr parse();

private:
    Ptr parseMethod();

    INode::Type parseType();

    std::vector< std::shared_ptr<Argument> > parseArgList();

    std::shared_ptr<Argument> parseArgument();

    std::vector<Ptr> parseBody();

    Ptr parseCommand();

    Ptr parseDeclaration();

    Ptr parseAssignment();

    Ptr parseReturn();

    Ptr parseFunctionCall();

    Ptr parsePrint();

    std::vector<Ptr> parseParamList();

    Ptr parseIF();

    std::vector<Ptr> getBodyWithBracket();

    IFNode::Sign parseSign();

    Ptr parseWHILE();

    Ptr parseExpression();

    Ptr parseTerm();

    Ptr parseFactor();

    Ptr parsePower();

    Ptr parseAtom();

private:
    TokenStream& tokenStream;

    std::unordered_map< std::string, INode::Type > typeVariable;
};

#endif // PARSER_HPP
