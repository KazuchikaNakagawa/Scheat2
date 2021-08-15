#ifndef EXPR
#define EXPR

#include "Node.h"

namespace nodes{

class Expr : public Node{
public:
    virtual Value *fcodegen() override{
        return nullptr;
    }
    virtual ~Expr(){};
    Expr(Parser &p, SourceLocation l) : Node(p, l){};
};

};

#endif
