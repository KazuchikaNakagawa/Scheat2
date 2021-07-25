#ifndef CALLTERM
#define CALLTERM

#include "Term.h"

namespace nodes {

class ArgumentExpr {
public:
    Scheat *scheato;
    Parser &parser;
    SourceLocation location;
    vector<Type *> types = {};
    unique_ptr<ArgumentExpr> args;
    unique_ptr<Expr> expr;
    ArgumentExpr(Parser &p, SourceLocation l, unique_ptr<Expr> e)
    : parser(p), location(l)
    {
        args = nullptr;
        expr = move(e);
        types.push_back(expr->type);
    }
    ArgumentExpr(Parser &p) : parser(p){
        
    }
    vector<Value *> codegen(){
        vector<Value *> v = {};
        if (!args) v = args->codegen();
        v.push_back(expr->codegen());
    };
    static void addArgument(Parser &p,unique_ptr<ArgumentExpr> &a, unique_ptr<Expr> e){
        auto argExpr = make_unique<ArgumentExpr>(p);
        argExpr->args = move(a);
        argExpr->expr = move(e);
        argExpr->types = argExpr->args->types;
        argExpr->types.push_back(e->type);
        a = move(argExpr);
    }
    virtual ~ArgumentExpr(){};
};

class CallTerm : public Term {
    string func_name;
    unique_ptr<ArgumentExpr> args;
public:
    Value *codegen() override{
        auto callee = parser.module->getFunction(func_name);
        if (!callee){
            parser.scheato->logger()->FatalError(location, __FILE_NAME__, __LINE__,
            "function %s does not exists in module.", func_name.c_str());
        }
        std::vector<Value *> v = args->codegen();
        return parser.builder.CreateCall(callee, v, "calltmp");
    };
    virtual ~CallTerm() {};
    CallTerm(
        Parser &p,
        Type *t,
        SourceLocation l,
        string fname,
        unique_ptr<ArgumentExpr> a
    )
    : Term(p, l)
    {
        func_name = fname;
        type = t;
        args = move(a);
    }
};

} /* nodes */

#endif
