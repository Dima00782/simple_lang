#include "Program.hpp"

void Program::accept(IVisitor *visitor)
{
    visitor->visitProgram();
    for (auto method : methods)
    {
        method->accept(visitor);
    }
}

void Program::setMethods(const std::vector<std::shared_ptr<INode> >& value)
{
    methods = value;
}

