#ifndef PoOExpr
#define PoOExpr

#include "Expr.h"
#include "../Context.h"

namespace nodes {
class PostfixOperatorExpr : public Expr{
    shared_ptr<Expr> lhs;
    OperatorInfo *info;
public:
    Value *fcodegen() override{
        auto lv = lhs->codegen();
        Value *fv = nullptr;
        if (info->index >= 0) {
            fv = parser.builder.CreateStructGEP(info->type, lv, info->index);
        }else{
            fv = parser.module->getFunction(info->name);
        }
        std::vector<Value *> v = {lv};
        return parser.builder.CreateCall((FunctionType*)info->type, fv, v, "calltmp");
    };
    virtual ~PostfixOperatorExpr(){};
    PostfixOperatorExpr(
        Parser &p,
        Type *t,
        shared_ptr<Expr> lvalue,
        OperatorInfo *i
    )
    : Expr(p, lvalue->location)
    {
        type = t;
        lhs =  (lvalue);
        info = i;
    }
};
} /* nodes */

#endif
