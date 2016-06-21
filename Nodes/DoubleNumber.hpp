#ifndef DOUBLENUMBER_HPP
#define DOUBLENUMBER_HPP

#include "INode.hpp"

class DoubleNumber : public INode
{
public:
    DoubleNumber(double _value);

    virtual void accept(IVisitor *visitor) override;

    double getValue();

private:
    double value;
};

#endif // DOUBLENUMBER_HPP
