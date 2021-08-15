#ifndef PPoOExpr
#define PPoOExpr

#include "PrimaryExpr.h"
#include "../Context.h"

namespace nodes {
class PrimaryPostfixOperatorExpr : public PrimaryExpr{
    shared_ptr<PrimaryExpr> lhs;
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
    virtual ~PrimaryPostfixOperatorExpr(){};
    PrimaryPostfixOperatorExpr(
        Parser &p,
        Type *t,
        shared_ptr<PrimaryExpr> lvalue,
        OperatorInfo *i
    )
    : PrimaryExpr(p, lvalue->location)
    {
        lhs =  (lvalue);
        type = t;
        info = i;
    }
};
} /* nodes */

#endif
