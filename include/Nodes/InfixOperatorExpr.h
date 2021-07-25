#ifndef IOExpr
#define IOExpr

#include "Expr.h"

namespace nodes {

class InfixOperatorExpr : public Expr {
    unique_ptr<Expr> lhs;
    string func_name;
    unique_ptr<Expr> rhs;
public:
    Value *codegen() override;
    virtual ~InfixOperatorExpr() {};
    InfixOperatorExpr(Parser &, Type *, unique_ptr<Expr>, string, unique_ptr<Expr>);
};

}

#endif
