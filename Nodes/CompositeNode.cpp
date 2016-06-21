#include "CompositeNode.hpp"
#include <algorithm>
#include <stdexcept>

void CompositeNode::accept(IVisitor* visitor)
{
    for (auto node : nestedNodes)
    {
        node->accept(visitor);
    }
}

void CompositeNode::add(const std::shared_ptr<INode>& node)
{
    nestedNodes.push_back(node);
}

void CompositeNode::remove(const std::shared_ptr<INode>& node)
{
    auto iter = std::find(nestedNodes.begin(), nestedNodes.end(), node);
    if (nestedNodes.end() == iter)
    {
        throw std::logic_error("remove of a nonexistent element");
    }
    nestedNodes.erase(iter);
}
