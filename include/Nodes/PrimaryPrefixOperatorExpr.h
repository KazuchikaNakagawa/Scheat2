#ifndef PPOExpr
#define PPOExpr

#include "PrimaryExpr.h"
#include "../Context.h"
namespace nodes {

class PrimaryPrefixOperatorExpr : public PrimaryExpr {
    OperatorInfo *info;
    shared_ptr<PrimaryExpr> rhs;
public:
    Value *fcodegen() override{
        auto rv = rhs->codegen();
        Value *fv = nullptr;
        if (info->index >= 0) {
            fv = parser.builder.CreateStructGEP(info->type, rv, info->index);
        }else{
            fv = parser.module->getFunction(info->name);
        }
        std::vector<Value *> v = {rv};
        return parser.builder.CreateCall((FunctionType*)info->type, fv, v, "calltmp");
    };
    virtual ~PrimaryPrefixOperatorExpr(){};
    PrimaryPrefixOperatorExpr(
        Parser &p,
        Type *t,
        OperatorInfo *i,
        shared_ptr<PrimaryExpr> expr
    )
    : PrimaryExpr(p, expr->location)
    {
        type = t;
        rhs =  (expr);
        info = i;
    };
};

} /*nodes */

#endif
