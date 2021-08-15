#ifndef FUNCTIONDECLARESTATEMENT
#define FUNCTIONDECLARESTATEMENT

#include "Statement.h"

namespace nodes {

class FunctionDeclareStatement : public Statement, Expr {
    FunctionType *functionType;
    string name;
    vector<shared_ptr<Statement>> body;
public:
    Value *fcodegen() override{
        Function *F = Function::Create(functionType, Function::ExternalLinkage, name, parser.module.get());
        BasicBlock *BB = BasicBlock::Create(*TheContext, "entry", F);
        Builder->SetInsertPoint(BB);
        for (auto ptr : body){
            ptr->codegen();
        }
        verifyFunction(*F);
        return F;
    }
    virtual ~FunctionDeclareStatement(){};
    FunctionDeclareStatement(
        Parser &p,
        SourceLocation loc,
        string n,
        FunctionType *ft
    )
    : Statement(p, loc)
    {
        functionType = ft;
        name = n;
    }
    void addBody(shared_ptr<Statement> b) { body.push_back(b); };
};

} /* nodes */

#endif
