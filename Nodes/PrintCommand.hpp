#ifndef PRINTCOMMAND_HPP
#define PRINTCOMMAND_HPP

#include "INode.hpp"
#include <memory>

class PrintCommand : public INode
{
public:
    virtual void accept(IVisitor *visitor) override;

    std::shared_ptr<INode> getExpression() const;

    void setExpression(const std::shared_ptr<INode> &value);

private:
    std::shared_ptr<INode> expression;
};

#endif // PRINTCOMMAND_HPP
