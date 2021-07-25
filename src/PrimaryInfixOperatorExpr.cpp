#include "Nodes/PrimaryInfixOperatorExpr.h"

using namespace nodes;

Value *PrimaryInfixOperatorExpr::codegen(){
    auto callee = parser.module->getFunction(func_name);
    if (!callee){
        parser.scheato->logger()->FatalError(location, __FILE_NAME__, __LINE__,
        "function %s does not exists in module.", func_name.c_str());
    }
    std::vector<Value *> v = {lhs->codegen(), rhs->codegen()};
    return parser.builder.CreateCall(callee, v, "calltmp");
}

PrimaryInfixOperatorExpr::PrimaryInfixOperatorExpr
(
    Parser &p,
    Type *t,
    unique_ptr<PrimaryExpr> lvalue,
    string fname,
    unique_ptr<PrimaryExpr> rvalue
)
: PrimaryExpr(p, lvalue->location)
{
    type = t;
    lhs = move(lvalue);
    func_name = fname;
    rhs = move(rvalue);
}
