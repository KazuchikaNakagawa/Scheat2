#ifndef PIOExpr
#define PIOExpr

#include "PrimaryExpr.h"
#include "../Context.h"

namespace nodes {
class PrimaryInfixOperatorExpr : public PrimaryExpr {
    shared_ptr<PrimaryExpr> lhs;
    OperatorInfo *info;
    shared_ptr<PrimaryExpr> rhs;
public:
    Value *fcodegen() override;
    virtual ~PrimaryInfixOperatorExpr(){};
    PrimaryInfixOperatorExpr(
        Parser &,
        Type *,
        shared_ptr<PrimaryExpr>,
        OperatorInfo *i,
        shared_ptr<PrimaryExpr>
    );
};
}

#endif
