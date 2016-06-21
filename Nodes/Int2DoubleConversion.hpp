#ifndef INT2DOUBLECONVERSION_HPP
#define INT2DOUBLECONVERSION_HPP

#include "INode.hpp"
#include <memory>

class Int2DoubleConversion : public INode
{
public:
    Int2DoubleConversion(const std::shared_ptr<INode>& _node);

    // INode interface
public:
    virtual void accept(IVisitor *visitor) override;

private:
    std::shared_ptr<INode> node;
};

#endif // INT2DOUBLECONVERSION_HPP
