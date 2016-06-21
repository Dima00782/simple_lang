#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include "INode.hpp"
#include <vector>
#include <memory>

class Program : public INode
{
public:
    virtual void accept(IVisitor *visitor) override;

    void setMethods(const std::vector<std::shared_ptr<INode> >& value);

private:
    std::vector< std::shared_ptr<INode> > methods;
};

#endif // PROGRAM_HPP
