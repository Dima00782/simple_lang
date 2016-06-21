#ifndef IFNODE_HPP
#define IFNODE_HPP

#include "INode.hpp"
#include <memory>
#include <vector>

class IFNode : public INode
{
public:
    enum Sign
    {
        MORE,
        LESS,
        EQUALITY,
        MORE_OR_EQUALITY,
        LESS_OR_EQUALITY,
    };

public:
    virtual void accept(IVisitor *visitor) override;

    std::shared_ptr<INode> getLeftExpression() const;

    void setLeftExpression(const std::shared_ptr<INode> &value);

    std::shared_ptr<INode> getRightExpression() const;

    void setRightExpression(const std::shared_ptr<INode> &value);

    Sign getSign() const;

    void setSign(const Sign &value);

    std::vector<std::shared_ptr<INode> > getTrueBody() const;

    void setTrueBody(const std::vector<std::shared_ptr<INode> > &value);

    std::vector<std::shared_ptr<INode> > getFalseBody() const;

    void setFalseBody(const std::vector<std::shared_ptr<INode> > &value);

private:
    Sign sign;

    std::shared_ptr<INode> leftExpression;

    std::shared_ptr<INode> rightExpression;

    std::vector< std::shared_ptr<INode> > trueBody;

    std::vector< std::shared_ptr<INode> > falseBody;
};

#endif // IFNODE_HPP
