#include "Assignment.hpp"

void Assignment::accept(IVisitor *visitor)
{
    rvalue->accept(visitor);
    visitor->visitAssignment(this);
}

std::string Assignment::getLvalue() const
{
    return lvalue;
}

void Assignment::setLvalue(const std::string& value)
{
    lvalue = value;
}
std::shared_ptr<INode> Assignment::getRvalue() const
{
    return rvalue;
}

void Assignment::setRvalue(const std::shared_ptr<INode>& value)
{
    rvalue = value;
}

