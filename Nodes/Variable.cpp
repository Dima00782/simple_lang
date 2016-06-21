#include "Variable.hpp"

Variable::Variable(const std::string& _name)
    : name(_name)
{
}

void Variable::accept(IVisitor *visitor)
{
    visitor->visitVariable(this);
}

std::string Variable::getName() const
{
    return name;
}

