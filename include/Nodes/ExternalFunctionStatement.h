#ifndef EFStatement
#define EFStatement

#include "Statement.h"

namespace nodes {
class ExternalFunctionStatement : public Statement {
public:
    vector<Type *> argTypes;
    vector<string> argNames;
    Type *return_type;
    string func_name;
    Value *codegen() override{
        FunctionType *ft = FunctionType::get(return_type, argTypes, false);
        Function *F = Function::Create(ft, Function::ExternalLinkage, func_name, parser.module.get());
        int index = 0;
        for (auto& arg : F->args()){
            arg.setName(argNames[index++]);
        }
        return F;
    };
    ExternalFunctionStatement(
        Parser &p,
        SourceLocation l,
        Type *rt,
        string name,
        vector<Type *> types,
        vector<string> names
    )
    : Statement(p, l)
    {
        func_name = name;
        return_type = rt;
        argTypes = types;
        argNames = names;
    }
};
} /* nodes */

#endif
