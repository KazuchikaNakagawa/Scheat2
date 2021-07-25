#ifndef POTerm
#define POTerm

#include "Term.h"
namespace nodes {

class PrefixOperatorTerm : public Term {
    std::string func_name;
    unique_ptr<Term> rhs;
public:
    Value *codegen() override{
        auto callee = parser.module->getFunction(func_name);
        if (!callee){
            parser.scheato->logger()->FatalError(location, __FILE_NAME__, __LINE__,
            "function %s does not exists in module.", func_name.c_str());
        }
        std::vector<Value *> v = {rhs->codegen()};
        return parser.builder.CreateCall(callee, v, "calltmp");
    };
    virtual ~PrefixOperatorTerm(){};
    PrefixOperatorTerm(
        Parser &p,
        Type *t,
        string n,
        unique_ptr<Term> expr
    )
    : Term(p, expr->location)
    {
        type = t;
        rhs = move(expr);
        func_name = n;
    };
};

} /*nodes */

#endif
