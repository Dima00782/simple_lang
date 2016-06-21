#ifndef ASSIGNMENT_HPP
#define ASSIGNMENT_HPP

#include "INode.hpp"
#include <string>
#include <memory>

class Assignment : public INode
{
public:
    virtual void accept(IVisitor *visitor) override;

    std::string getLvalue() const;

    void setLvalue(const std::string& value);

    std::shared_ptr<INode> getRvalue() const;

    void setRvalue(const std::shared_ptr<INode>& value);

private:
    std::string lvalue;

    std::shared_ptr<INode> rvalue;
};

#endif // ASSIGNMENT_HPP
