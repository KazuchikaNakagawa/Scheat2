#ifndef POExpr
#define POExpr

#include "Expr.h"
#include "../Context.h"
namespace nodes {

class PrefixOperatorExpr : public Expr {
    OperatorInfo *info;
    shared_ptr<Expr> rhs;
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
    virtual ~PrefixOperatorExpr(){};
    PrefixOperatorExpr(
        Parser &p,
        Type *t,
        OperatorInfo * i,
        shared_ptr<Expr> expr
    )
    : Expr(p, expr->location)
    {
        type = t;
        rhs =  (expr);
        info = i;
    };
};

} /*nodes */

#endif
