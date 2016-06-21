#include "Return.hpp"

Return::Return()
    : expression(nullptr)
{}

void Return::accept(IVisitor *visitor)
{
    if (nullptr != expression)
    {
        expression->accept(visitor);
    }
    visitor->visitReturn(this);
}

std::shared_ptr<INode> Return::getExpression() const
{
    return expression;
}

void Return::setExpression(const std::shared_ptr<INode>& value)
{
    expression = value;
}
