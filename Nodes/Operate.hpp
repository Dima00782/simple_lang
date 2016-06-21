#ifndef OPERATE_HPP
#define OPERATE_HPP

#include "CompositeNode.hpp"
#include <string>

class Operate : public CompositeNode
{
public:
    enum Type
    {
        PLUS,
        MINUS,
        ASTERISK,
        DEGREE,
        SLASH,
    };

public:
    Operate() {}

    Operate(Type type_);

    virtual void accept(IVisitor* visitor) override;

    Type getOperateType();

private:
    Type type;
};

#endif // OPERATE_HPP
