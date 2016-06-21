#include "Parser.hpp"
#include "Nodes/IntNumber.hpp"
#include "Nodes/DoubleNumber.hpp"
#include "Nodes/Operate.hpp"
#include "Nodes/Method.hpp"
#include "Nodes/Int2DoubleConversion.hpp"
#include "Nodes/Argument.hpp"
#include "Nodes/Declaration.hpp"
#include "Nodes/Return.hpp"
#include "Nodes/Assignment.hpp"
#include "Nodes/Program.hpp"
#include "Nodes/FunctionCall.hpp"
#include "Nodes/Variable.hpp"
#include "Nodes/PrintCommand.hpp"
#include "Nodes/IFnode.hpp"
#include "Nodes/WhileNode.hpp"

#include <stdexcept>
#include <cassert>

Parser::Parser(TokenStream& _tokenStream)
    : tokenStream(_tokenStream)
{
}

Parser::Ptr Parser::parse()
{
    std::vector< std::shared_ptr<INode> > methods;
    Token nextToken = tokenStream.get();

    while (Token::END_STREAM != nextToken.type)
    {
        tokenStream.putBack(nextToken);
        Ptr method = parseMethod();
        methods.push_back(method);
        nextToken = tokenStream.get();
    }

    auto program = std::make_shared<Program>();
    program->setMethods(methods);

    return program;
}

Parser::Ptr Parser::parseMethod()
{
    typeVariable.clear();
    auto method = std::make_shared<Method>();

    method->setType(parseType());

    Token nextToken = tokenStream.get();
    if (Token::NAME != nextToken.type)
    {
        throw std::logic_error("miss method name");
    }
    method->setName(nextToken.value);

    nextToken = tokenStream.get();
    if (Token::ROUND_OPEN_BRACKET != nextToken.type)
    {
        throw std::logic_error("miss round open bracket : method");
    }

    method->setArgumentList(parseArgList());
    nextToken = tokenStream.get();
    if (Token::ROUND_CLOSE_BRACKET != nextToken.type)
    {
        throw std::logic_error("miss round close bracket : method");
    }

    nextToken = tokenStream.get();
    if (Token::FIGURE_OPEN_BRACKET != nextToken.type)
    {
        throw std::logic_error("miss figure open bracket : method");
    }
    method->setBody(parseBody());
    nextToken = tokenStream.get();
    if (Token::FIGURE_CLOSE_BRACKET != nextToken.type)
    {
        throw std::logic_error("miss figure close bracket : method");
    }

    return method;
}

INode::Type Parser::parseType()
{
    Token token = tokenStream.get();
    switch (token.type) {
    case Token::INT:
        return INode::INT;
    case Token::DOUBLE:
        return INode::DOUBLE;
    case Token::VOID:
        return INode::VOID;
    default:
        throw std::logic_error("wrong type : type");
    }
}

std::vector< std::shared_ptr<Argument> > Parser::parseArgList()
{
    std::vector< std::shared_ptr<Argument> > argumentList;
    Token token = tokenStream.get();

    while (Token::ROUND_CLOSE_BRACKET != token.type)
    {
        tokenStream.putBack(token);
        argumentList.push_back(parseArgument());
        token = tokenStream.get();
        if (Token::COMMA != token.type && Token::ROUND_CLOSE_BRACKET != token.type)
        {
            throw std::logic_error("missing comma : argument list");
        }

        if (Token::ROUND_CLOSE_BRACKET != token.type)
        {
            token = tokenStream.get();
        }
    }
    tokenStream.putBack(token);

    return argumentList;
}

std::shared_ptr<Argument> Parser::parseArgument()
{
    auto argument = std::make_shared<Argument>();
    INode::Type type = parseType();
    argument->setType(type);

    Token token = tokenStream.get();
    if (Token::NAME == token.type)
    {
        argument->setName(token.value);
    }
    else
    {
        throw std::logic_error("miss argument name : argument");
    }

    assert(typeVariable.end() == typeVariable.find(token.value));
    typeVariable[token.value] = type;

    return argument;
}

std::vector<Parser::Ptr> Parser::parseBody()
{
    std::vector<Ptr> body;

    Token token = tokenStream.get();

    while (Token::FIGURE_CLOSE_BRACKET != token.type)
    {
        tokenStream.putBack(token);
        body.push_back(parseCommand());
        token = tokenStream.get();
        if (Token::SEMICOLON != token.type && Token::FIGURE_CLOSE_BRACKET != token.type)
        {
            throw std::logic_error("missing semicolon : body");
        }

        if (Token::FIGURE_CLOSE_BRACKET != token.type)
        {
            token = tokenStream.get();
        }
    }
    tokenStream.putBack(token);

    return body;
}

Parser::Ptr Parser::parseCommand()
{
    Ptr command;
    Token token = tokenStream.get();

    switch (token.type)
    {
        case Token::INT: case Token::DOUBLE: case Token::VOID:
        {
            tokenStream.putBack(token);
            command = parseDeclaration();
            break;
        }
        case Token::NAME:
        {
            Token nextToken = tokenStream.get();
            if (Token::ROUND_OPEN_BRACKET == nextToken.type)
            {
                tokenStream.putBack(token);
                tokenStream.putBack(nextToken);
                command = parseFunctionCall();
            }
            else if (Token::EQUALITY == nextToken.type)
            {
                tokenStream.putBack(token);
                tokenStream.putBack(nextToken);
                command = parseAssignment();
            }
            break;
        }
        case Token::RETURN:
        {
            tokenStream.putBack(token);
            command = parseReturn();
            break;
        }
        case Token::PRINT:
        {
            tokenStream.putBack(token);
            command = parsePrint();
            break;
        }
        case Token::IF:
        {
            tokenStream.putBack(token);
            command = parseIF();
            break;
        }
        case Token::WHILE:
        {
            tokenStream.putBack(token);
            command = parseWHILE();
            break;
        }
    default:
        throw std::logic_error("not a command " + token.value + " : command");
    }

    return command;
}

Parser::Ptr Parser::parseDeclaration()
{
    auto declaration = std::make_shared<Declaration>();

    INode::Type type = parseType();
    declaration->setType(type);

    Token token = tokenStream.get();
    if (Token::NAME == token.type)
    {
        declaration->setName(token.value);
    }
    else
    {
        throw std::logic_error("missing name : declaration");
    }

    typeVariable[token.value] = type;

    return declaration;
}

Parser::Ptr Parser::parseAssignment()
{
    auto assignment = std::make_shared<Assignment>();

    Token token = tokenStream.get();
    if (Token::NAME == token.type)
    {
        assignment->setLvalue(token.value);
    }
    else
    {
        throw std::logic_error("missing name : assignment");
    }

    token = tokenStream.get();
    if (Token::EQUALITY != token.type)
    {
        throw std::logic_error("missing equality : assignment");
    }

    assignment->setRvalue(parseExpression());

    return assignment;
}

Parser::Ptr Parser::parseReturn()
{
    auto returnNode = std::make_shared<Return>();
    Token token = tokenStream.get();

    if (Token::RETURN == token.type)
    {
        token = tokenStream.get();
        if (Token::SEMICOLON != token.type)
        {
            tokenStream.putBack(token);
            returnNode->setExpression(parseExpression());
        }
    }
    else
    {
        throw std::logic_error("missing return : return");
    }

    return returnNode;
}

Parser::Ptr Parser::parseFunctionCall()
{
    auto functionCallNode = std::make_shared<FunctionCall>();

    Token token = tokenStream.get();
    if (Token::NAME != token.type)
    {
        throw std::logic_error("miss function name : parseFunctionCall");
    }
    functionCallNode->setFunctionName(token.value);

    token = tokenStream.get();
    if (Token::ROUND_OPEN_BRACKET == token.type)
    {
        functionCallNode->setParamList(parseParamList());
        token = tokenStream.get();
        if (Token::ROUND_CLOSE_BRACKET != token.type)
        {
            throw std::logic_error("missing close bracket : function call");
        }
    }
    else
    {
        throw std::logic_error("missing open bracket : function call");
    }

    return functionCallNode;
}

Parser::Ptr Parser::parsePrint()
{
    auto printCommand = std::make_shared<PrintCommand>();
    Token token = tokenStream.get();

    if (Token::PRINT != token.type)
    {
        throw std::logic_error("missing print : print");
    }

    printCommand->setExpression(parseExpression());

    return printCommand;
}

std::vector<Parser::Ptr> Parser::parseParamList()
{
    std::vector<Ptr> parameterList;
    Token token = tokenStream.get();

    while (Token::ROUND_CLOSE_BRACKET != token.type)
    {
        tokenStream.putBack(token);
        parameterList.push_back(parseExpression());
        token = tokenStream.get();
        if (Token::COMMA != token.type && Token::ROUND_CLOSE_BRACKET != token.type)
        {
            throw std::logic_error("missing comma : argument list");
        }

        if (Token::ROUND_CLOSE_BRACKET != token.type)
        {
            token = tokenStream.get();
        }
    }
    tokenStream.putBack(token);

    return parameterList;
}

IFNode::Sign Parser::parseSign()
{
    Token token = tokenStream.get();

    switch (token.type)
    {
        case Token::LESS:
        {
            Token nextToken = tokenStream.get();
            if (Token::EQUALITY == nextToken.type)
            {
                return IFNode::LESS_OR_EQUALITY;
            }
            else
            {
                tokenStream.putBack(nextToken);
                return IFNode::LESS;
            }
        }
        case Token::MORE:
        {
            Token nextToken = tokenStream.get();
            if (Token::EQUALITY == nextToken.type)
            {
                return IFNode::MORE_OR_EQUALITY;
            }
            else
            {
                tokenStream.putBack(nextToken);
                return IFNode::MORE;
            }
        }
        case Token::EQUALITY:
        {
            Token nextToken = tokenStream.get();
            if (Token::EQUALITY != nextToken.type)
            {
                throw std::logic_error("wrong second symbol equality : parseIF");
            }
            return IFNode::EQUALITY;
        }
        default:
            throw std::logic_error("wrong symbol comparison : parseIF");
    }
}

Parser::Ptr Parser::parseIF()
{
    auto ifStatement = std::make_shared<IFNode>();
    Token token = tokenStream.get();

    if (Token::IF != token.type)
    {
        throw std::logic_error("missing if : parseIF");
    }

    token = tokenStream.get();
    if (Token::ROUND_OPEN_BRACKET != token.type)
    {
        throw std::logic_error("missing round open bracket : parseIF");
    }

    ifStatement->setLeftExpression(parseExpression());
    ifStatement->setSign(parseSign());
    ifStatement->setRightExpression(parseExpression());

    token = tokenStream.get();
    if (Token::ROUND_CLOSE_BRACKET != token.type)
    {
        throw std::logic_error("missing round close bracket : parseIF");
    }

    ifStatement->setTrueBody(getBodyWithBracket());

    token = tokenStream.get();
    if (Token::ELSE == token.type)
    {
        ifStatement->setFalseBody(getBodyWithBracket());
    }
    else
    {
        tokenStream.putBack(token);
    }

    return ifStatement;
}

std::vector<Parser::Ptr> Parser::getBodyWithBracket()
{
    Token token = tokenStream.get();
    if (Token::FIGURE_OPEN_BRACKET != token.type)
    {
        throw std::logic_error("missing round close bracket : parseIF");
    }

    auto body = parseBody();

    token = tokenStream.get();
    if (Token::FIGURE_CLOSE_BRACKET != token.type)
    {
        throw std::logic_error("missing round close bracket : parseIF");
    }

    return body;
}

Parser::Ptr Parser::parseWHILE()
{
    auto whileStatement = std::make_shared<WhileNode>();
    Token token = tokenStream.get();

    if (Token::WHILE != token.type)
    {
        throw std::logic_error("missing while : parseWHILE");
    }

    token = tokenStream.get();
    if (Token::ROUND_OPEN_BRACKET != token.type)
    {
        throw std::logic_error("missing round open bracket : parseWHILE");
    }

    whileStatement->setLeftExpression(parseExpression());
    whileStatement->setSign(parseSign());
    whileStatement->setRightExpression(parseExpression());

    token = tokenStream.get();
    if (Token::ROUND_CLOSE_BRACKET != token.type)
    {
        throw std::logic_error("missing round close bracket : parseIF");
    }

    whileStatement->setBody(getBodyWithBracket());

    return whileStatement;
}

Parser::Ptr Parser::parseExpression()
{
    Ptr expression = parseTerm();
    Token nextToken = tokenStream.get();

    if (Token::Type::MINUS == nextToken.type || Token::Type::PLUS == nextToken.type)
    {
        std::shared_ptr<Operate> operate;

        if (Token::Type::PLUS == nextToken.type)
        {
            operate = std::make_shared<Operate>(Operate::Type::PLUS);
        }
        else if (Token::Type::MINUS == nextToken.type)
        {
            operate = std::make_shared<Operate>(Operate::Type::MINUS);
        }

        Ptr nextExpression = parseExpression();
        if (0 == (expression->getType() & nextExpression->getType()))
        {
            if (INode::DOUBLE == expression->getType() && INode::INT == nextExpression->getType())
            {
                nextExpression = std::make_shared<Int2DoubleConversion>(nextExpression);
            }
            else if (INode::INT == expression->getType() && INode::DOUBLE == nextExpression->getType())
            {
                expression = std::make_shared<Int2DoubleConversion>(expression);
            }
        }
        operate->add(expression);
        operate->add(nextExpression);
        if (INode::DOUBLE == expression->getType() || INode::DOUBLE == nextExpression->getType())
        {
            operate->setType(INode::DOUBLE);
        }

        if (INode::INT == expression->getType() && INode::INT == nextExpression->getType())
        {
            operate->setType(INode::INT);
        }

        expression = operate;
    }
    else
    {
        tokenStream.putBack(nextToken);
    }

    return expression;
}

Parser::Ptr Parser::parseTerm()
{
    Ptr term = parseFactor();
    Token nextToken = tokenStream.get();

    if (Token::Type::ASTERISK == nextToken.type || Token::Type::SLASH == nextToken.type)
    {
        std::shared_ptr<Operate> operate;

        if (Token::Type::ASTERISK == nextToken.type)
        {
            operate = std::make_shared<Operate>(Operate::Type::ASTERISK);
        }
        else if (Token::Type::SLASH == nextToken.type)
        {
            operate = std::make_shared<Operate>(Operate::Type::SLASH);
        }

        Ptr nextTerm = parseTerm();
        if (0 == (term->getType() & nextTerm->getType()))
        {
            if (INode::DOUBLE == term->getType() && INode::INT == nextTerm->getType())
            {
                nextTerm = std::make_shared<Int2DoubleConversion>(nextTerm);
            }
            else if (INode::INT == term->getType() && INode::DOUBLE == nextTerm->getType())
            {
                term = std::make_shared<Int2DoubleConversion>(term);
            }
        }
        operate->add(term);
        operate->add(nextTerm);

        if (INode::DOUBLE == term->getType() || INode::DOUBLE == nextTerm->getType())
        {
            operate->setType(INode::DOUBLE);
        }

        if (INode::INT == term->getType() && INode::INT == nextTerm->getType())
        {
            operate->setType(INode::INT);
        }

        term = operate;
    }
    else
    {
        tokenStream.putBack(nextToken);
    }

    return term;
}

Parser::Ptr Parser::parseFactor()
{
    Ptr factor = parsePower();
    Token nextToken = tokenStream.get();

    if (Token::Type::DEGREE == nextToken.type)
    {
        auto operate = std::make_shared<Operate>(Operate::Type::DEGREE);
        Ptr nextFactor = parseFactor();
        if (0 == (factor->getType() & nextFactor->getType()))
        {
            if (INode::DOUBLE == factor->getType() && INode::INT == nextFactor->getType())
            {
                nextFactor = std::make_shared<Int2DoubleConversion>(nextFactor);
            }
            else if (INode::INT == factor->getType() && INode::DOUBLE == nextFactor->getType())
            {
                factor = std::make_shared<Int2DoubleConversion>(factor);
            }
        }

        operate->add(factor);
        operate->add(nextFactor);

        if (INode::DOUBLE == factor->getType() || INode::DOUBLE == nextFactor->getType())
        {
            operate->setType(INode::DOUBLE);
        }

        if (INode::INT == factor->getType() && INode::INT == nextFactor->getType())
        {
            operate->setType(INode::INT);
        }

        factor = operate;
    }
    else
    {
        tokenStream.putBack(nextToken);
    }

    return factor;
}

Parser::Ptr Parser::parsePower()
{
    Ptr power = parseAtom();
    Token nextToken = tokenStream.get();
    tokenStream.putBack(nextToken);

//    if (Token::Type::MINUS == nextToken.type)
//    {
//        auto operate = std::make_shared<Operate>(Operate::Type::MINUS);
//        operate->add(power);
//        power = operate;
//    }
//    else
//    {
//        tokenStream.putBack(nextToken);
//    }

    return power;
}

Parser::Ptr Parser::parseAtom()
{
    Ptr atom;
    Token token = tokenStream.get();

    if (Token::NUMBER_INT == token.type)
    {
        atom = std::make_shared<IntNumber>(std::stoi(token.value));
        atom->setType(INode::INT);
    }
    else if (Token::NUMBER_DOUBLE == token.type)
    {
        atom = std::make_shared<DoubleNumber>(std::stod(token.value));
        atom->setType(INode::DOUBLE);
    }
    else if (Token::ROUND_OPEN_BRACKET == token.type)
    {
        atom = parseExpression();
        token = tokenStream.get();
        if (Token::ROUND_CLOSE_BRACKET != token.type)
        {
            // not logic_error, need parserException
            throw std::logic_error("missing round close bracket");
        }
    }
    else if (Token::NAME == token.type)
    {
        Token nextToken = tokenStream.get();
        if (Token::ROUND_OPEN_BRACKET == nextToken.type)
        {
            tokenStream.putBack(token);
            tokenStream.putBack(nextToken);
            atom = parseFunctionCall();
        }
        else
        {
            tokenStream.putBack(nextToken);
            atom = std::make_shared<Variable>(token.value);
            assert(typeVariable.end() != typeVariable.find(token.value));
            atom->setType(typeVariable[token.value]);
        }
    }
    else
    {
        tokenStream.putBack(token);
    }

    return atom;
}
