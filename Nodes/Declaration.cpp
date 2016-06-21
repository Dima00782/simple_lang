#include "Declaration.hpp"

void Declaration::accept(IVisitor *visitor)
{
    visitor->visitDeclaration(this);
}

void Declaration::setName(const std::string& _name)
{
    name = _name;
}

std::string Declaration::getName()
{
    return name;
}
