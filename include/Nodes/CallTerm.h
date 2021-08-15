#ifndef CALLTERM
#define CALLTERM

#include "IdentifierTerm.h"

namespace nodes {

class ArgumentExpr {
public:
    Scheat *scheato;
    Parser &parser;
    SourceLocation location;
    shared_ptr<ArgumentExpr> args;
    shared_ptr<Expr> expr;
    vector<Type *> types = {};
    ArgumentExpr(Parser &p, SourceLocation l, shared_ptr<Expr> e)
    : parser(p), location(l)
    {
        args = nullptr;
        expr =  (e);
        types.push_back(expr->type);
    }
    ArgumentExpr(Parser &p) : parser(p){

    }
    vector<Value *> codegen(){
        vector<Value *> v = {};
        if (!args) v = args->codegen();
        v.push_back(expr->codegen());
        return v;
    };
    static void addArgument(Parser &p,shared_ptr<ArgumentExpr> &a, shared_ptr<Expr> e){
        auto argExpr = make_shared<ArgumentExpr>(p);
        argExpr->args =  (a);
        argExpr->expr =  (e);
        argExpr->types = argExpr->args->types;
        argExpr->types.push_back(e->type);
        a =  (argExpr);
    }
    virtual ~ArgumentExpr(){};
};

class CallTerm : public IdentifierTerm {
    shared_ptr<Expr> func_expr;
    shared_ptr<ArgumentExpr> args;
public:
    Value *fcodegen() override{
        auto fv = func_expr->codegen();
        vector<Value *> v = args->codegen();
        return parser.builder.CreateCall((FunctionType *)func_expr->type, fv, v, "calltmp");
    };
    virtual ~CallTerm() {};
    CallTerm(
        Parser &p,
        Type *t,
        SourceLocation l,
        shared_ptr<Expr> fname,
        shared_ptr<ArgumentExpr> a
    )
    : IdentifierTerm(p, l)
    {
        func_expr = fname;
        type = t;
        args =  (a);
    }
    void addArgument(shared_ptr<Expr> e) {
        ArgumentExpr::addArgument(parser, args, e);
    }
};

} /* nodes */

#endif
