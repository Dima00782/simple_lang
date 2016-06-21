#include "PrintCommand.hpp"

void PrintCommand::accept(IVisitor *visitor)
{
    visitor->visitPrintCommand(this);
}
std::shared_ptr<INode> PrintCommand::getExpression() const
{
    return expression;
}

void PrintCommand::setExpression(const std::shared_ptr<INode>& value)
{
    expression = value;
}

