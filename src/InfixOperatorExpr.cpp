#include "Nodes/InfixOperatorExpr.h"

using namespace nodes;
InfixOperatorExpr::InfixOperatorExpr(Parser &p, Type *t,unique_ptr<Expr> lvalue, string name, unique_ptr<Expr> rvalue) : Expr(p, lvalue->location){
    lhs = move(lvalue);
    rhs = move(rvalue);
    func_name = name;
    type = t;
}

Value *InfixOperatorExpr::codegen(){
    auto callee = parser.module->getFunction(func_name);
    if (!callee){
        parser.scheato->logger()->FatalError(location, __FILE_NAME__, __LINE__,
        "function %s does not exists in module.", func_name.c_str());
    }
    std::vector<Value *> v = {lhs->codegen(), rhs->codegen()};
    return parser.builder.CreateCall(callee, v, "calltmp");
}
