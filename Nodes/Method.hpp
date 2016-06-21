#ifndef METHOD_HPP
#define METHOD_HPP

#include "INode.hpp"
#include "Argument.hpp"
#include <memory>
#include <string>
#include <vector>
#include <cstddef>

class Method : public INode
{
public:
    virtual void accept(IVisitor* visitor) override;

    void setName(const std::string& _name);

    std::string getName();

    void setBody(const std::vector< std::shared_ptr<INode> >& _body);

    void setArgumentList(const std::vector< std::shared_ptr<Argument> >& _argumentList);

    std::vector< std::shared_ptr<Argument> > getArgumentList();

private:
    std::string name;

    std::vector< std::shared_ptr<INode> > body;

    std::vector< std::shared_ptr<Argument> > argumentList;
};

#endif // METHOD_HPP
