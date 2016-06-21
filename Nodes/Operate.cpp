#include "Operate.hpp"

Operate::Operate(Operate::Type type_)
    : type(type_)
{
}

void Operate::accept(IVisitor* visitor)
{
    CompositeNode::accept(visitor);
    visitor->visitOperate(this);
}

Operate::Type Operate::getOperateType()
{
    return type;
}
