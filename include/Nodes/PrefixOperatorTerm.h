#ifndef POTerm
#define POTerm

#include "Term.h"
#include "../Context.h"
namespace nodes {

class PrefixOperatorTerm : public Term {
    OperatorInfo *info;
    shared_ptr<Term> rhs;
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
    virtual ~PrefixOperatorTerm(){};
    PrefixOperatorTerm(
        Parser &p,
        Type *t,
        OperatorInfo *i,
        shared_ptr<Term> expr
    )
    : Term(p, expr->location)
    {
        type = t;
        rhs =  (expr);
        info = i;
    };
};

} /*nodes */

#endif
