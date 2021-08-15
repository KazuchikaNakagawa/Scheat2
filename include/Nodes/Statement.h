#ifndef STATEMENT
#define STATEMENT

#include "Node.h"
namespace nodes {

class Statement : public Node{
public:
    virtual Value *fcodegen() override{
        return nullptr;
    };
    virtual ~Statement(){
    };
    Statement(Parser &p, SourceLocation l)
    : Node (p,l)
    {
        type = Type::getVoidTy(parser.context);
    };
};

} /* nodes */

#endif
