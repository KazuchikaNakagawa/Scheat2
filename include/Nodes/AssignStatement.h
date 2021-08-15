#ifndef ASSIGNSTATEMENT
#define ASSIGNSTATEMENT

#include "Statement.h"

namespace nodes {
class AssignStatement : public Statement {
    shared_ptr<Expr> ptr;
    shared_ptr<Expr> value;
public:
    Value *fcodegen() override{
        auto lvalue = ptr->codegen();
        auto rvalue = value->codegen();

        return parser.builder.CreateStore(rvalue, lvalue);
    };
    virtual ~AssignStatement(){};
    AssignStatement(
        Parser &p,
        shared_ptr<Expr> pt,
        shared_ptr<Expr> v
    )
    : Statement(p, pt->location)
    {
        ptr =  (pt);
        value =  (v);
    }
};
} /* nodes */

#endif
