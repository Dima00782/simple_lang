#ifndef ARGUMENT_HPP
#define ARGUMENT_HPP

#include "INode.hpp"
#include <string>

class Argument : public INode
{
public:
    virtual void accept(IVisitor *visitor) override;

    void setName(const std::string& _name);

    std::string getName();

private:
    std::string name;
};

#endif // ARGUMENT_HPP
