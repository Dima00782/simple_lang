#include "DoubleNumber.hpp"

DoubleNumber::DoubleNumber(double _value)
    : value(_value)
{
}

void DoubleNumber::accept(IVisitor *visitor)
{
    visitor->visitDoubleNumber(this);
}

double DoubleNumber::getValue()
{
    return value;
}
