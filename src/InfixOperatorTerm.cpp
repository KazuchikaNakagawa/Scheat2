#include "Nodes/InfixOperatorTerm.h"

using namespace nodes;

Value *InfixOperatorTerm::codegen(){
    auto callee = parser.module->getFunction(func_name);
    if (!callee){
        parser.scheato->logger()->FatalError(location, __FILE_NAME__, __LINE__,
        "function %s does not exists in module.", func_name.c_str());
    }
    std::vector<Value *> v = {lhs->codegen(), rhs->codegen()};
    return parser.builder.CreateCall(callee, v, "calltmp");
}

InfixOperatorTerm::InfixOperatorTerm(
    Parser &p,
    Type *t,
    unique_ptr<Term> lvalue,
    string fname,
    unique_ptr<Term> rvalue
)
: Term(p, lvalue->location)
{
    lhs = move(lvalue);
    func_name = fname;
    rhs = move(rvalue);
    type = t;
}
