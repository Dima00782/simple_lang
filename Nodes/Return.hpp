#ifndef RETURN_HPP
#define RETURN_HPP

#include "INode.hpp"
#include <memory>

class Return : public INode
{
public:
    Return();

    virtual void accept(IVisitor *visitor) override;

    std::shared_ptr<INode> getExpression() const;

    void setExpression(const std::shared_ptr<INode>& value);

private:
    std::shared_ptr<INode> expression;
};

#endif // RETURN_HPP
