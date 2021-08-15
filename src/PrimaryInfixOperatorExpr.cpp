#include "Nodes/PrimaryInfixOperatorExpr.h"

using namespace nodes;

Value *PrimaryInfixOperatorExpr::fcodegen(){
    auto lv = lhs->codegen();
    Value *fv = nullptr;
    if (info->index >= 0) {
        fv = parser.builder.CreateStructGEP(info->type, lv, info->index);
    }else{
        fv = parser.module->getFunction(info->name);
    }
    std::vector<Value *> v = {lv, rhs->codegen()};
    return parser.builder.CreateCall((FunctionType*)info->type, fv, v, "calltmp");
}

PrimaryInfixOperatorExpr::PrimaryInfixOperatorExpr
(
    Parser &p,
    Type *t,
    shared_ptr<PrimaryExpr> lvalue,
    OperatorInfo *i,
    shared_ptr<PrimaryExpr> rvalue
)
: PrimaryExpr(p, lvalue->location)
{
    type = t;
    lhs =  (lvalue);
    info = i;
    rhs =  (rvalue);
}
