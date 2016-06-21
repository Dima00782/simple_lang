#ifndef DECLARATION_HPP
#define DECLARATION_HPP

#include "INode.hpp"
#include <string>

class Declaration : public INode
{
public:
    virtual void accept(IVisitor *visitor) override;

    void setName(const std::string& _name);

    std::string getName();

private:
    std::string name;
};

#endif // DECLARATION_HPP
