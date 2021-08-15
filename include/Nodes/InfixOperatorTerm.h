#ifndef IOTerm
#define IOTerm

#include "Term.h"
#include "../Context.h"

namespace nodes {
class InfixOperatorTerm : public Term {
    shared_ptr<Term> lhs;
    OperatorInfo *info;
    shared_ptr<Term> rhs;
public:
    Value *fcodegen() override;
    virtual ~InfixOperatorTerm(){};
    InfixOperatorTerm(
        Parser &,
        Type *,
        shared_ptr<Term>,
        OperatorInfo *,
        shared_ptr<Term>
    );
};
}

#endif
