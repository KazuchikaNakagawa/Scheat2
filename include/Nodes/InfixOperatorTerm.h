#ifndef IOTerm
#define IOTerm

#include "Term.h"

namespace nodes {
class InfixOperatorTerm : public Term {
    unique_ptr<Term> lhs;
    string func_name;
    unique_ptr<Term> rhs;
public:
    Value *codegen() override;
    virtual ~InfixOperatorTerm(){};
    InfixOperatorTerm(
        Parser &,
        Type *,
        unique_ptr<Term>,
        string,
        unique_ptr<Term>
    );
};
}

#endif
