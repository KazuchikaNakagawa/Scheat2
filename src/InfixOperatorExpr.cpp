#include "Nodes/InfixOperatorExpr.h"

using namespace nodes;
InfixOperatorExpr::InfixOperatorExpr(Parser &p, Type *t,shared_ptr<Expr> lvalue, OperatorInfo *i, shared_ptr<Expr> rvalue) : Expr(p, lvalue->location){
    lhs =  (lvalue);
    rhs =  (rvalue);
    info = i;
    type = t;
}

Value *InfixOperatorExpr::fcodegen(){
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
