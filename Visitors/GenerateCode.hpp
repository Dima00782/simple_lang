#ifndef GENERATECODE_HPP
#define GENERATECODE_HPP

#include "IVisitor.hpp"

#include "Nodes/Operate.hpp"
#include "Nodes/IntNumber.hpp"
#include "Nodes/DoubleNumber.hpp"
#include "Nodes/Method.hpp"
#include "Nodes/Int2DoubleConversion.hpp"
#include "Nodes/Argument.hpp"
#include "Nodes/Assignment.hpp"
#include "Nodes/Declaration.hpp"
#include "Nodes/FunctionCall.hpp"
#include "Nodes/PrintCommand.hpp"
#include "Nodes/Program.hpp"
#include "Nodes/Return.hpp"
#include "Nodes/Variable.hpp"
#include "Nodes/IFnode.hpp"
#include "Nodes/WhileNode.hpp"

#include <string>
#include <cstddef>
#include <unordered_map>

class GenerateCode : public IVisitor
{
public:
    GenerateCode();

    std::string getCode();

    // IVisitor interface
    void visitOperate(Operate *operate);
    void visitIntNumber(IntNumber *number);
    void visitDoubleNumber(DoubleNumber *number);
    void visitInt2DoubleConversion();
    void visitMethod(Method *method);
    void visitAssignment(Assignment *assignmentNode);
    void visitDeclaration(Declaration *declarationNode);
    void visitFunctionCall(FunctionCall *functionCall);
    void visitPrintCommand(PrintCommand *printCommand);
    void visitReturn(Return *returnNode);
    void visitArgument(Argument* argument);
    void visitIF(IFNode* ifNode);
    void visitWHILE(WhileNode *whileNode);
    void visitVariable(Variable *variableNode);    
    void visitProgram();

private:
    struct VariableInfo
    {
        VariableInfo(size_t _localNumber, INode::Type _type)
            : localNumber(_localNumber)
            , type(_type)
        {}

        VariableInfo()
        {}

        size_t localNumber;
        INode::Type type;
    };

private:
    std::string stringCode;

    std::string body;

    std::string onPrint;

    size_t limitStack;

    size_t indexVariable;

    size_t indexLabel;

    std::unordered_map< std::string, VariableInfo > variablesTable;

    std::unordered_map< std::string, std::string > functionsTable;

    static const size_t SIZE_ONE_STACK_OPERAND = 1;

    static const std::string LOAD_ON_STACK_COMMAND;
    static const std::string LOAD_ON_STACK_DOUBLE_COMMAND;

    static const std::string ADD_TWO_DOUBLE_NUMBER_ON_STACK_COMMAND;
    static const std::string MUL_TWO_DOUBLE_NUMBER_ON_STACK_COMMAND;
    static const std::string SUB_TWO_DOUBLE_NUMBER_ON_STACK_COMMAND;
    static const std::string DIV_TWO_DOUBLE_NUMBER_ON_STACK_COMMAND;
    static const std::string POW_TWO_DOUBLE_NUMBER_ON_STACK_COMMAND;

    static const std::string ADD_TWO_INT_NUMBER_ON_STACK_COMMAND;
    static const std::string MUL_TWO_INT_NUMBER_ON_STACK_COMMAND;
    static const std::string SUB_TWO_INT_NUMBER_ON_STACK_COMMAND;
    static const std::string DIV_TWO_INT_NUMBER_ON_STACK_COMMAND;
    static const std::string POW_TWO_INT_NUMBER_ON_STACK_COMMAND;

    static const std::string I2D_COMMAND;

private:
    std::string getMangleName(Method* method);

    std::string getPrefixByType(INode::Type type);

    std::string getPrifixByCompare(IFNode::Sign sign);
};

#endif // GENERATEEXPRESSIONCODE_HPP
