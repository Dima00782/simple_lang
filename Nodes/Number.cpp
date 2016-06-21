#include "Number.hpp"

Number::Number(double value_)
    : value(value_)
{
}

void Number::accept(IVisitor* visitor)
{
    visitor->visitNumber(this);
}

double Number::getValue()
{
    return value;
}
