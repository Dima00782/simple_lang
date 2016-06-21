#include "FunctionCall.hpp"

void FunctionCall::accept(IVisitor *visitor)
{
    for (auto parameter : paramList)
    {
        parameter->accept(visitor);
    }

    visitor->visitFunctionCall(this);
}

std::string FunctionCall::getFunctionName() const
{
    return functionName;
}

void FunctionCall::setFunctionName(const std::string &value)
{
    functionName = value;
}

std::vector<std::shared_ptr<INode> > FunctionCall::getParamList() const
{
    return paramList;
}

void FunctionCall::setParamList(const std::vector<std::shared_ptr<INode> >& value)
{
    paramList = value;
}


