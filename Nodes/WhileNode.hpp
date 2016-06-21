#ifndef WHILENODE_HPP
#define WHILENODE_HPP

#include "INode.hpp"
#include "IFnode.hpp"
#include <memory>
#include <vector>

class WhileNode : public INode
{
public:
    virtual void accept(IVisitor *visitor) override;

    IFNode::Sign getSign() const;

    void setSign(const IFNode::Sign &value);

    std::shared_ptr<INode> getLeftExpression() const;

    void setLeftExpression(const std::shared_ptr<INode> &value);

    std::shared_ptr<INode> getRightExpression() const;

    void setRightExpression(const std::shared_ptr<INode> &value);

    std::vector<std::shared_ptr<INode> > getBody() const;

    void setBody(const std::vector<std::shared_ptr<INode> > &value);

private:
    IFNode::Sign sign;

    std::shared_ptr<INode> leftExpression;

    std::shared_ptr<INode> rightExpression;

    std::vector< std::shared_ptr<INode> > body;
};

#endif // WHILENODE_HPP
