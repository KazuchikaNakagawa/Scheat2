#ifndef EXPRSTATEMENT
#define EXPRSTATEMENT

#include "Statement.h"
namespace nodes {

class ExprStatement : public Statement {
    unique_ptr<Expr> ptr;
public:
    virtual Value *codegen(){
        ptr->codegen();
        return nullptr;
    }
    virtual ~ExprStatement(){};
    ExprStatement(Parser &p, unique_ptr<Expr> e)
    : Statement(p,e->location)
    {
        ptr = move(e);
    };
};

} /* nodes */

#endif
