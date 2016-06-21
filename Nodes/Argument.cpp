#include "Argument.hpp"

void Argument::accept(IVisitor *visitor)
{
    visitor->visitArgument(this);
}

void Argument::setName(const std::string &_name)
{
    name = _name;
}

std::string Argument::getName()
{
    return name;
}
