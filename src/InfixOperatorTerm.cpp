#include "Nodes/InfixOperatorTerm.h"

using namespace nodes;

Value *InfixOperatorTerm::fcodegen(){
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

InfixOperatorTerm::InfixOperatorTerm(
    Parser &p,
    Type *t,
    shared_ptr<Term> lvalue,
    OperatorInfo *i,
    shared_ptr<Term> rvalue
)
: Term(p, lvalue->location)
{
    lhs =  (lvalue);
    info = i;
    rhs =  (rvalue);
    type = t;
}
