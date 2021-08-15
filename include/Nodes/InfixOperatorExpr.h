#ifndef IOExpr
#define IOExpr

#include "Expr.h"
#include "../Context.h"

namespace nodes {

class InfixOperatorExpr : public Expr {
    shared_ptr<Expr> lhs;
    OperatorInfo *info;
    shared_ptr<Expr> rhs;
public:
    Value *fcodegen() override;
    virtual ~InfixOperatorExpr() {};
    InfixOperatorExpr(Parser &, Type *, shared_ptr<Expr>, OperatorInfo *, shared_ptr<Expr>);
};

}

#endif
