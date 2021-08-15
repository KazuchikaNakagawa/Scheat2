#ifndef EFStatement
#define EFStatement

#include "Statement.h"
#include "Expr.h"

namespace nodes {
class ExternalFunctionStatement : public Statement, Expr {
public:
    Type *return_type;
    string func_name;
    Value *fcodegen() override{
        Function *F = Function::Create((FunctionType*)type, Function::ExternalLinkage, func_name, parser.module.get());
        int index = 0;
        for (auto& arg : F->args()){
            arg.setName("arg"+to_string(index++));
        }
        return F;
    };
    ExternalFunctionStatement(
        Parser &p,
        SourceLocation l,
        string name,
        FunctionType *rt
        //vector<string> names
    )
    : Statement(p, l)
    {
        func_name = name;
        return_type = rt->getReturnType();
        type = rt;
        //argNames = names;
    }
};
} /* nodes */

#endif
