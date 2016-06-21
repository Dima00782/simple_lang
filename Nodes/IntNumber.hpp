#ifndef INTNUMBER_HPP
#define INTNUMBER_HPP

#include "INode.hpp"

class IntNumber : public INode
{
public:
    IntNumber(int _value);

    virtual void accept(IVisitor* visitor) override;

    int getValue();

private:
    int value;
};

#endif // INTNUMBER_HPP
