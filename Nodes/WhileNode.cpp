#include "WhileNode.hpp"

void WhileNode::accept(IVisitor *visitor)
{
    visitor->visitWHILE(this);
}

IFNode::Sign WhileNode::getSign() const
{
    return sign;
}

void WhileNode::setSign(const IFNode::Sign &value)
{
    sign = value;
}

std::shared_ptr<INode> WhileNode::getLeftExpression() const
{
    return leftExpression;
}

void WhileNode::setLeftExpression(const std::shared_ptr<INode> &value)
{
    leftExpression = value;
}

std::shared_ptr<INode> WhileNode::getRightExpression() const
{
    return rightExpression;
}

void WhileNode::setRightExpression(const std::shared_ptr<INode> &value)
{
    rightExpression = value;
}

std::vector<std::shared_ptr<INode> > WhileNode::getBody() const
{
    return body;
}

void WhileNode::setBody(const std::vector<std::shared_ptr<INode> > &value)
{
    body = value;
}
