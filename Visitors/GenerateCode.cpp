#include "GenerateCode.hpp"
#include <stdexcept>
#include <cctype>
#include <cassert>

const std::string GenerateCode::LOAD_ON_STACK_COMMAND                     = "    ldc                ";
const std::string GenerateCode::LOAD_ON_STACK_DOUBLE_COMMAND              = "    ldc2_w              ";

const std::string GenerateCode::ADD_TWO_DOUBLE_NUMBER_ON_STACK_COMMAND    = "    dadd               ";
const std::string GenerateCode::MUL_TWO_DOUBLE_NUMBER_ON_STACK_COMMAND    = "    dmul               ";
const std::string GenerateCode::SUB_TWO_DOUBLE_NUMBER_ON_STACK_COMMAND    = "    dsub               ";
const std::string GenerateCode::DIV_TWO_DOUBLE_NUMBER_ON_STACK_COMMAND    = "    ddiv               ";
const std::string GenerateCode::POW_TWO_DOUBLE_NUMBER_ON_STACK_COMMAND    = "   invokestatic          java/lang/Math/pow(DD)D";

const std::string GenerateCode::ADD_TWO_INT_NUMBER_ON_STACK_COMMAND       = "    iadd               ";
const std::string GenerateCode::MUL_TWO_INT_NUMBER_ON_STACK_COMMAND       = "    imul               ";
const std::string GenerateCode::SUB_TWO_INT_NUMBER_ON_STACK_COMMAND       = "    isub               ";
const std::string GenerateCode::DIV_TWO_INT_NUMBER_ON_STACK_COMMAND       = "    idiv               ";

const std::string GenerateCode::I2D_COMMAND                               = "    i2d                ";

GenerateCode::GenerateCode()
    : limitStack(0)
    , indexVariable(0)
    , indexLabel(0)
{
}

void GenerateCode::visitOperate(Operate *operateNode)
{
    limitStack += SIZE_ONE_STACK_OPERAND;

    switch (operateNode->getOperateType())
    {
        case Operate::Type::PLUS :
        {
            if (INode::DOUBLE == operateNode->getType())
            {
                body += ADD_TWO_DOUBLE_NUMBER_ON_STACK_COMMAND;
            }
            else if (INode::INT == operateNode->getType())
            {
                body += ADD_TWO_INT_NUMBER_ON_STACK_COMMAND;
            }
            break;
        }
        case Operate::Type::MINUS :
        {
            if (INode::DOUBLE == operateNode->getType())
            {
                body += SUB_TWO_DOUBLE_NUMBER_ON_STACK_COMMAND;
            }
            else if (INode::INT == operateNode->getType())
            {
                body += SUB_TWO_INT_NUMBER_ON_STACK_COMMAND;
            }
            break;
        }
        case Operate::Type::ASTERISK :
        {
            if (INode::DOUBLE == operateNode->getType())
            {
                body += MUL_TWO_DOUBLE_NUMBER_ON_STACK_COMMAND;
            }
            else if (INode::INT == operateNode->getType())
            {
                body += MUL_TWO_INT_NUMBER_ON_STACK_COMMAND;
            }
            break;
        }
        case Operate::Type::SLASH :
        {
            if (INode::DOUBLE == operateNode->getType())
            {
                body += DIV_TWO_DOUBLE_NUMBER_ON_STACK_COMMAND;
            }
            else if (INode::INT == operateNode->getType())
            {
                body += DIV_TWO_INT_NUMBER_ON_STACK_COMMAND;
            }
            break;
        }
        case Operate::Type::DEGREE :
        {
            body += POW_TWO_DOUBLE_NUMBER_ON_STACK_COMMAND;
            break;
        }
    default:
        throw std::logic_error("undefined operation");
    }
    body += '\n';
}

void GenerateCode::visitIntNumber(IntNumber* intNumber)
{
    limitStack += SIZE_ONE_STACK_OPERAND;
    body += LOAD_ON_STACK_COMMAND + std::to_string(intNumber->getValue()) + '\n';
}

void GenerateCode::visitDoubleNumber(DoubleNumber* doubleNumber)
{
    limitStack += 2 * SIZE_ONE_STACK_OPERAND;
    body += LOAD_ON_STACK_DOUBLE_COMMAND + std::to_string(doubleNumber->getValue()) + '\n';
}

void GenerateCode::visitInt2DoubleConversion()
{
    body += I2D_COMMAND + '\n';
}

void GenerateCode::visitMethod(Method* method)
{
    stringCode += ".method                  public static " + getMangleName(method) + '\n';
    stringCode += ".limit stack          " + std::to_string(limitStack + 1) + '\n';
    stringCode += ".limit locals          " + std::to_string(indexVariable) + '\n';
    stringCode += body;
    stringCode += ".end method\n\n";

    indexVariable = 0;
    limitStack = 0;
    body.clear();
    variablesTable.clear();
}

std::string GenerateCode::getMangleName(Method* method)
{
    std::string mangleName = method->getName() + '(';

    for (auto argument : method->getArgumentList())
    {
        mangleName += getPrefixByType(argument->getType());
    }

    if ("main" == method->getName())
    {
        mangleName += "[Ljava/lang/String;";
        ++indexVariable;
    }

    mangleName += ')';

    mangleName += getPrefixByType(method->getType());

    if (INode::DOUBLE == method->getType())
    {
        ++indexVariable;
    }

    functionsTable[method->getName()] = mangleName;

    return mangleName;
}

std::string GenerateCode::getPrefixByType(INode::Type type)
{
    switch (type) {
    case INode::INT:
        return "I";
    case INode::DOUBLE:
        return "D";
    case INode::VOID:
        return "V";
    default:
        return "I";
        // to fix
        throw std::logic_error("wrong type : getPrefixByType");
    }
}

std::string GenerateCode::getPrifixByCompare(IFNode::Sign sign)
{
    switch (sign) {
    case IFNode::LESS:
        return "ge";
    case IFNode::LESS_OR_EQUALITY:
        return "gt";
    case IFNode::MORE:
        return "le";
    case IFNode::MORE_OR_EQUALITY:
        return "lt";
    case IFNode::EQUALITY:
        return "ne";
    default:
        throw std::logic_error("wrond sign : getPrifixByCompare");
    }
}

void GenerateCode::visitAssignment(Assignment *assignmentNode)
{
    VariableInfo info = variablesTable[assignmentNode->getLvalue()];
    std::string prefix = getPrefixByType(info.type);
    prefix[0] = std::tolower(prefix[0]);
    body += prefix + "store " + std::to_string(info.localNumber) + '\n';
}

void GenerateCode::visitDeclaration(Declaration *declarationNode)
{
    variablesTable.emplace(declarationNode->getName(), VariableInfo(indexVariable, declarationNode->getType()) );

    ++indexVariable;
    if (INode::DOUBLE == declarationNode->getType())
    {
        ++indexVariable;
    }
}

void GenerateCode::visitFunctionCall(FunctionCall *functionCall)
{
    body += "invokestatic          Main/" + functionsTable[functionCall->getFunctionName()] + "\n";
}

void GenerateCode::visitPrintCommand(PrintCommand *printCommand)
{
    body += "getstatic             java/lang/System/out Ljava/io/PrintStream;\n";
    printCommand->getExpression()->accept(this);
    body += "invokevirtual         java/io/PrintStream/println(" + getPrefixByType(printCommand->getExpression()->getType()) + ")V\n";
}

void GenerateCode::visitReturn(Return *returnNode)
{
    auto expression = returnNode->getExpression();
    if (nullptr != expression)
    {
        std::string prefix = getPrefixByType(expression->getType());
        prefix[0] = std::tolower(prefix[0]);
        body += prefix;
    }

    body += "return\n";
}

void GenerateCode::visitArgument(Argument *argument)
{
    assert(variablesTable.end() == variablesTable.find(argument->getName()));
    variablesTable.emplace(argument->getName(), VariableInfo(indexVariable, argument->getType()));
    ++indexVariable;
}

void GenerateCode::visitIF(IFNode *ifNode)
{
    // print argument
    if (IFNode::LESS == ifNode->getSign() || IFNode::LESS_OR_EQUALITY == ifNode->getSign())
    {
        ifNode->getRightExpression()->accept(this);
        ifNode->getLeftExpression()->accept(this);
    }
    else
    {
        ifNode->getLeftExpression()->accept(this);
        ifNode->getRightExpression()->accept(this);
    }

    // print compare string
    if (INode::INT == ifNode->getLeftExpression()->getType())
    {
        body += std::string("if_icmp") + getPrifixByCompare(ifNode->getSign()) + ' ';
    }

    size_t indexForLabel = body.size();

    // print body with "true"
    for (auto statement : ifNode->getTrueBody())
    {
        statement->accept(this);
    }

    // print label and body with "false"
    body += std::string("Label") + std::to_string(indexLabel) + ":\n";

    // correct label with condition
    body.insert(indexForLabel, std::string("Label") + std::to_string(indexLabel) + "\n");
    ++indexLabel;

    for (auto statement : ifNode->getFalseBody())
    {
        statement->accept(this);
    }
}

void GenerateCode::visitWHILE(WhileNode *whileNode)
{
    body += std::string("Label") + std::to_string(indexLabel) + ":\n";
    int beginLabelIndex = indexLabel;
    ++indexLabel;

    if (IFNode::LESS == whileNode->getSign() || IFNode::LESS_OR_EQUALITY == whileNode->getSign())
    {
        whileNode->getRightExpression()->accept(this);
        whileNode->getLeftExpression()->accept(this);
    }
    else
    {
        whileNode->getLeftExpression()->accept(this);
        whileNode->getRightExpression()->accept(this);
    }

    if (INode::INT == whileNode->getLeftExpression()->getType())
    {
        body += std::string("if_icmp") + getPrifixByCompare(whileNode->getSign()) + std::string(" Label") + std::to_string(indexLabel) + '\n';
    }

    for (auto statement : whileNode->getBody())
    {
        statement->accept(this);
    }
    body += std::string("goto ") + "Label" + std::to_string(beginLabelIndex) + '\n';
    body += std::string("Label") + std::to_string(beginLabelIndex + 1) + ":\n";
}

void GenerateCode::visitVariable(Variable *variableNode)
{
    assert(variablesTable.end() != variablesTable.find(variableNode->getName()));

    VariableInfo info = variablesTable[variableNode->getName()];
    std::string prefix = getPrefixByType(info.type);
    prefix[0] = std::tolower(prefix[0]);
    body += prefix + "load " + std::to_string(info.localNumber) + '\n';
}

void GenerateCode::visitProgram()
{
    stringCode +=
            ".source                  Main.java\n" \
            ".class                   public Main\n" \
            ".super                   java/lang/Object\n" \
            ".method                  public <init>()V\n"\
            ".limit stack          1\n" \
            ".limit locals         1\n" \
            ".line                 1\n" \
            "aload_0\n" \
            "invokespecial         java/lang/Object/<init>()V\n" \
            "return\n" \
            ".end method\n\n";
}

std::string GenerateCode::getCode()
{
    return stringCode;
}
