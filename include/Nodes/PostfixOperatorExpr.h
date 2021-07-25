#ifndef PoOExpr
#define PoOExpr

#include "Expr.h"

namespace nodes {
class PostfixOperatorExpr : public Expr{
    unique_ptr<Expr> lhs;
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
    virtual ~PostfixOperatorExpr(){};
    PostfixOperatorExpr(
        Parser &p,
        Type *t,
        unique_ptr<Expr> lvalue,
        string fname
    )
    : Expr(p, lhs->location)
    {
        type = t;
        lhs = move(lvalue);
        func_name = fname;
    }
};
} /* nodes */

#endif
