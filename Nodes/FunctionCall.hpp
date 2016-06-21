#ifndef FUNCTIONCALL_HPP
#define FUNCTIONCALL_HPP

#include "INode.hpp"
#include <string>
#include <memory>
#include <vector>

class FunctionCall : public INode
{
public:
    virtual void accept(IVisitor *visitor) override;

    std::string getFunctionName() const;

    void setFunctionName(const std::string& value);

    std::vector<std::shared_ptr<INode> > getParamList() const;

    void setParamList(const std::vector<std::shared_ptr<INode> >& value);

private:
    std::string functionName;

    std::vector< std::shared_ptr<INode> > paramList;
};

#endif // FUNCTIONCALL_HPP
