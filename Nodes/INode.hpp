#ifndef INODE_HPP
#define INODE_HPP

#include "Visitors/IVisitor.hpp"

class INode
{
public:
    enum Type
    {
        INT     = 1,
        DOUBLE  = 1 << 1,
        VOID    = 1 << 2
    };

public:
    virtual void accept(IVisitor* visitor) = 0;

    Type getType() { return type; }

    void setType(Type _type) { type = _type; }

    virtual ~INode() {}

private:
    Type type;
};

#endif // INODE_HPP
