#ifndef EXPRSTATEMENT
#define EXPRSTATEMENT

#include "Statement.h"
namespace nodes {

class ExprStatement : public Statement {
    shared_ptr<Expr> ptr;
public:
    virtual Value *fcodegen(){
        ptr->codegen();
        return nullptr;
    }
    virtual ~ExprStatement(){};
    ExprStatement(Parser &p, shared_ptr<Expr> e)
    : Statement(p,e->location)
    {
        ptr =  (e);
    };
};

} /* nodes */

#endif
