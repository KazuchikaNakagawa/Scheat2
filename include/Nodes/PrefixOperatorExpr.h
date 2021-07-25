#ifndef POExpr
#define POExpr

#include "Expr.h"
namespace nodes {

class PrefixOperatorExpr : public Expr {
    std::string func_name;
    unique_ptr<Expr> rhs;
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
    virtual ~PrefixOperatorExpr(){};
    PrefixOperatorExpr(
        Parser &p,
        Type *t,
        string n,
        unique_ptr<Expr> expr
    )
    : Expr(p, expr->location)
    {
        type = t;
        rhs = move(expr);
        func_name = n;
    };
};

} /*nodes */

#endif
