#include "Method.hpp"
#include "Argument.hpp"
#include <stdexcept>

void Method::accept(IVisitor* visitor)
{
    for (auto argument : argumentList)
    {
        argument->accept(visitor);
    }

    for (auto command : body)
    {
        command->accept(visitor);
    }

    visitor->visitMethod(this);
}

void Method::setName(const std::string& _name)
{
    name = _name;
}

std::string Method::getName()
{
    return name;
}

void Method::setBody(const std::vector< std::shared_ptr<INode> >& _body)
{
    body = _body;
}

void Method::setArgumentList(const std::vector<std::shared_ptr<Argument> > &_argumentList)
{
    argumentList = _argumentList;
}

std::vector<std::shared_ptr<Argument> > Method::getArgumentList()
{
    return argumentList;
}
