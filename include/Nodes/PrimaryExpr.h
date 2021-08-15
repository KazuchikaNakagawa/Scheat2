#ifndef PRIMARYEXPR
#define PRIMARYEXPR
#include "Expr.h"

namespace nodes {
class PrimaryExpr : public Expr {
public:
    virtual Value *fcodegen() override{
        return nullptr;
    }
    virtual ~PrimaryExpr(){};
    PrimaryExpr(Parser &p, SourceLocation l) : Expr(p,l){};
};

};

#endif
