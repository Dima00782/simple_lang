#ifndef VARIABLE_HPP
#define VARIABLE_HPP

#include "INode.hpp"
#include <string>

class Variable : public INode
{
public:
    Variable(const std::string& _name);

    virtual void accept(IVisitor *visitor) override;

    std::string getName() const;

private:
    std::string name;
};

#endif // VARIABLE_HPP
