#ifndef IVISITOR_HPP
#define IVISITOR_HPP

class Operate;
class IntNumber;
class DoubleNumber;
class Int2DoubleConversion;
class Method;
class Assignment;
class Declaration;
class FunctionCall;
class PrintCommand;
class Return;
class Argument;
class Variable;
class Program;
class IFNode;
class WhileNode;

class IVisitor
{
public:
    virtual void visitOperate(Operate* operate) = 0;

    virtual void visitIntNumber(IntNumber* number) = 0;

    virtual void visitDoubleNumber(DoubleNumber* number) = 0;

    virtual void visitInt2DoubleConversion() = 0;

    virtual void visitMethod(Method* method) = 0;

    virtual void visitAssignment(Assignment* method) = 0;

    virtual void visitDeclaration(Declaration* method) = 0;

    virtual void visitFunctionCall(FunctionCall* method) = 0;

    virtual void visitPrintCommand(PrintCommand* method) = 0;

    virtual void visitReturn(Return* method) = 0;

    virtual void visitVariable(Variable* method) = 0;

    virtual void visitIF(IFNode* ifNode) = 0;

    virtual void visitWHILE(WhileNode* ifNode) = 0;

    virtual void visitArgument(Argument* argument) = 0;

    virtual void visitProgram() = 0;

    virtual ~IVisitor() {}
};

#endif // IVISITOR_HPP
