#include "IntNumber.hpp"

IntNumber::IntNumber(int _value)
    : value(_value)
{
}

void IntNumber::accept(IVisitor *visitor)
{
    visitor->visitIntNumber(this);
}

int IntNumber::getValue()
{
    return value;
}
