#include "IFnode.hpp"

void IFNode::accept(IVisitor *visitor)
{
    visitor->visitIF(this);
}

std::shared_ptr<INode> IFNode::getLeftExpression() const
{
    return leftExpression;
}

void IFNode::setLeftExpression(const std::shared_ptr<INode> &value)
{
    leftExpression = value;
}

std::shared_ptr<INode> IFNode::getRightExpression() const
{
    return rightExpression;
}

void IFNode::setRightExpression(const std::shared_ptr<INode> &value)
{
    rightExpression = value;
}

IFNode::Sign IFNode::getSign() const
{
    return sign;
}

void IFNode::setSign(const Sign &value)
{
    sign = value;
}
std::vector<std::shared_ptr<INode> > IFNode::getTrueBody() const
{
    return trueBody;
}

void IFNode::setTrueBody(const std::vector<std::shared_ptr<INode> > &value)
{
    trueBody = value;
}

std::vector<std::shared_ptr<INode> > IFNode::getFalseBody() const
{
    return falseBody;
}

void IFNode::setFalseBody(const std::vector<std::shared_ptr<INode> > &value)
{
    falseBody = value;
}
