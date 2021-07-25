#ifndef PoOTerm
#define PoOTerm

#include "Term.h"

namespace nodes {
class PostfixOperatorTerm : public Term{
    unique_ptr<Term> lhs;
    string func_name;
public:
    Value *codegen() override{
        auto callee = parser.module->getFunction(func_name);
        if (!callee){
            parser.scheato->logger()->FatalError(location, __FILE_NAME__, __LINE__,
            "function %s does not exists in module.", func_name.c_str());
        }
        std::vector<Value *> v = {lhs->codegen()};
        return parser.builder.CreateCall(callee, v, "calltmp");
    };
    virtual ~PostfixOperatorTerm(){};
    PostfixOperatorTerm(
        Parser &p,
        Type *t,
        unique_ptr<Term> lvalue,
        string fname
    )
    : Term(p, lhs->location)
    {
        type = t;
        lhs = move(lvalue);
        func_name = fname;
    }
};
} /* nodes */

#endif
