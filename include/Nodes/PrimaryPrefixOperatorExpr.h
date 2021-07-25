#ifndef PPOExpr
#define PPOExpr

#include "PrimaryExpr.h"
namespace nodes {

class PrimaryPrefixOperatorExpr : public PrimaryExpr {
    std::string func_name;
    unique_ptr<PrimaryExpr> rhs;
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
    virtual ~PrimaryPrefixOperatorExpr(){};
    PrimaryPrefixOperatorExpr(
        Parser &p,
        Type *t,
        string n,
        unique_ptr<PrimaryExpr> expr
    )
    : PrimaryExpr(p, expr->location)
    {
        type = t;
        rhs = move(expr);
        func_name = n;
    };
};

} /*nodes */

#endif
