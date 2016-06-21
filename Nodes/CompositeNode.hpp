#ifndef COMPOSITENODE_HPP
#define COMPOSITENODE_HPP

#include "INode.hpp"
#include <memory>
#include <vector>

class CompositeNode : public INode
{
public:
    virtual void accept(IVisitor* visitor) override;

    void add(const std::shared_ptr<INode>& node);

    void remove(const std::shared_ptr<INode>& node);

private:
    std::vector< std::shared_ptr<INode> > nestedNodes;
};

#endif // COMPOSITENODE_HPP
