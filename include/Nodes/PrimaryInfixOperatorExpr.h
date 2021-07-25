#ifndef PIOExpr
#define PIOExpr

#include "PrimaryExpr.h"

namespace nodes {
class PrimaryInfixOperatorExpr : public PrimaryExpr {
    unique_ptr<PrimaryExpr> lhs;
    string func_name;
    unique_ptr<PrimaryExpr> rhs;
public:
    Value *codegen() override;
    virtual ~PrimaryInfixOperatorExpr(){};
    PrimaryInfixOperatorExpr(
        Parser &,
        Type *,
        unique_ptr<PrimaryExpr>,
        string,
        unique_ptr<PrimaryExpr>
    );
};
}

#endif
