#ifndef LOADEXPR
#define LOADEXPR

#include "Term.h"

class LoadTerm : public Term {
private:
    shared_ptr<Expr> value;
public:
    Value *fcodegen() override{
        if (!value->type->isPointerTy()) {
            return nullptr;
        }
        auto v = value->codegen();
        return parser.builder.CreateLoad(value->type->getPointerElementType(), v);
    }
    LoadExpr(
        Parser &p,
        shared_ptr<Expr> ptr
    )
    : Term(p, ptr->location)
    {
        value = ptr;
        type = ptr->type->getPointerElementType();
    };
    virtual ~LoadExpr();
};

#endif
