#include "Int2DoubleConversion.hpp"

Int2DoubleConversion::Int2DoubleConversion(const std::shared_ptr<INode>& _node)
    : node(_node)
{
    setType(INode::DOUBLE);
}

void Int2DoubleConversion::accept(IVisitor *visitor)
{
    node->accept(visitor);
    visitor->visitInt2DoubleConversion();
}
