#ifndef PoOTerm
#define PoOTerm

#include "Term.h"
#include "../Context.h"

namespace nodes {
class PostfixOperatorTerm : public Term{
    shared_ptr<Term> lhs;
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
    virtual ~PostfixOperatorTerm(){};
    PostfixOperatorTerm(
        Parser &p,
        Type *t,
        shared_ptr<Term> lvalue,
        OperatorInfo * i
    )
    : Term(p, lvalue->location)
    {
        type = t;
        lhs =  (lvalue);
        info = i;
    }
};
} /* nodes */

#endif
