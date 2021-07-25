#ifndef PPoOExpr
#define PPoOExpr

#include "PrimaryExpr.h"

namespace nodes {
class PrimaryPostfixOperatorExpr : public PrimaryExpr{
    unique_ptr<PrimaryExpr> lhs;
    string func_name;
public:
    Value *codegen() override{
        auto callee = parser.module->getFunction(func_name);
        if (!callee){
            scheato->logger()->FatalError(location, __FILE_NAME__, __LINE__,
            "function %s does not exists in module.", func_name.c_str());
        }
        std::vector<Value *> v = {lhs->codegen()};
        return parser.builder.CreateCall(callee, v, "calltmp");
    };
    virtual ~PrimaryPostfixOperatorExpr(){};
    PrimaryPostfixOperatorExpr(
        Parser &p,
        Type *t,
        unique_ptr<PrimaryExpr> lvalue,
        string fname
    )
    : PrimaryExpr(p, lhs->location)
    {
        lhs = move(lvalue);
        type = t;
        func_name = fname;
    }
};
} /* nodes */

#endif
