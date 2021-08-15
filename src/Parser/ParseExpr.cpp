#include "Parser.h"
#include "Nodes/AllNodes.h"
#include "Context/Variable.h"

shared_ptr<Expr> Parser::parseOperatedExpr(){
    shared_ptr<Expr> expr;
    if (tokens->kind == TokenKind::val_operator) {
        auto opTok = tokens;
        eat();
        expr = parseExpr();
        if (!expr) {
            return nullptr;
        }
        auto c = global->classes[convert(expr->type)];
        auto pair = c->operators.find(opTok->encodeOperator(scheato->logger()));
        if (pair == c->operators.end()) {
            tokens = opTok;
            goto next;
        }
        auto p = pair->second;
        if (p->precidence != OperatorInfo::secondary) {
            tokens = opTok;
            goto next;
        }
        if (p->position != OperatorInfo::prefix) {
            scheato->logger()->FatalError(
                getLocation(),
                __FILE_NAME__,
                __LINE__,
                "%s is not prefix operator.",
                opTok->value.strValue.c_str()
            );
            return nullptr;
        }
        if (!p->type->isFunctionTy()) {
            scheato->logger()->FatalError(
                getLocation(),
                __FILE_NAME__,
                __LINE__,
                "SystemError: %s is not function.",
                opTok->encodeOperator(scheato->logger()).c_str()
            );
            return nullptr;
        }
        auto arg = make_shared<ArgumentExpr>(*this, getLocation(), expr);
        if (p->index < 0) {
            // this operator is static.
            string fname = convert(expr->type)+opTok->encodeOperator(scheato->logger());
            auto pair = global->globals.find(fname);
            if (pair == global->globals.end()) {
                scheato->logger()->FatalError(
                    getLocation(),
                    __FILE_NAME__,
                    __LINE__,
                    "SystemError: %s is on class, but not in global",
                    opTok->encodeOperator(scheato->logger()).c_str()
                );
                return nullptr;
            }
            auto f = pair->second;
            if (!f->type()->isFunctionTy()) {
                scheato->logger()->FatalError(
                    getLocation(),
                    __FILE_NAME__,
                    __LINE__,
                    "SystemError: %s is not function.",
                    opTok->encodeOperator(scheato->logger()).c_str()
                );
                return nullptr;
            }
            auto it = make_shared<IdentifierTerm>(*this, opTok->location);
            it->name = fname;
            expr = make_shared<CallTerm>(*this, ((FunctionType*)f->type())->getReturnType(), getLocation(), it,  (arg));
            goto op;
        }else{
            scheato->logger()->FatalError(getLocation(),__FILE_NAME__,__LINE__,"member-operator is not available yet.");
            return nullptr;
        }
    }
next:
    expr = parsePrimaryExpr();
op:
    if (tokens->kind == TokenKind::val_operator) {
        auto opTok = tokens;
        eat();
        auto c = global->classes[convert(expr->type)];
        auto pair = c->operators.find(opTok->encodeOperator(scheato->logger()));
        if (pair == c->operators.end()) {
            scheato->logger()->FatalError(
                getLocation(),
                __FILE_NAME__,
                __LINE__,
                "type %s has no operator %s",
                convert(expr->type).c_str(),
                opTok->value.strValue.c_str()
            );
            return nullptr;
        }
        auto p = pair->second;
        if (nextIsValue()){
            if (p->position != OperatorInfo::postfix) {
                scheato->logger()->FatalError(
                    getLocation(),
                    __FILE_NAME__,
                    __LINE__,
                    "%s is not postfix operator.",
                    opTok->value.strValue.c_str()
                );
                return nullptr;
            }
            return make_shared<PostfixOperatorExpr>(*this, ((FunctionType*)p->type)->getReturnType(),  (expr), p);
        }else{
            auto expr2 = parseExpr();
            if (!expr) {
                return nullptr;
            }
            if (p->position != OperatorInfo::infix) {
                scheato->logger()->FatalError(
                    getLocation(),
                    __FILE_NAME__,
                    __LINE__,
                    "%s is not infix operator.",
                    opTok->value.strValue.c_str()
                );
                return nullptr;
            }
            return make_shared<InfixOperatorExpr>(*this, ((FunctionType*)p->type)->getReturnType(),  (expr), p,  (expr2));
        }
    }
    return expr;
}

shared_ptr<Expr> Parser::parseExpr(){

    // expr

    // operatedExpr
    //   op expr
    //   expr op expr
    //   expr op
    //   primary
    //
    // expr id
    // the expr
    // this expr

    shared_ptr<Expr> expr;
    if (tokens->kind == TokenKind::val_operator) {
        expr = parseOperatedExpr();
        if (!expr) {
            return nullptr;
        }
    }

    // this id(unknown)
    else if (tokens->kind == TokenKind::tok_this) {
        expr = parseNewIdentifierExpr();
        if (!expr) {
            return nullptr;
        }else{
            goto op;
        }
    }

    // the id
    else if (tokens->kind == TokenKind::tok_the) {
        eat();

        expr = parseIdentifierTerm();
        if (!expr) {
            return nullptr;
        }else{
            goto op;
        }
    }
op:
    if (tokens->kind == TokenKind::val_operator) {
        auto opTok = tokens;
        eat();
        auto c = global->classes[convert(expr->type)];
        auto pair = c->operators.find(opTok->encodeOperator(scheato->logger()));
        if (pair == c->operators.end()) {
            scheato->logger()->FatalError(
                getLocation(),
                __FILE_NAME__,
                __LINE__,
                "type %s has no operator %s",
                convert(expr->type).c_str(),
                opTok->value.strValue.c_str()
            );
            return nullptr;
        }
        auto p = pair->second;
        if (nextIsValue()){
            if (p->position != OperatorInfo::postfix) {
                scheato->logger()->FatalError(
                    getLocation(),
                    __FILE_NAME__,
                    __LINE__,
                    "%s is not postfix operator.",
                    opTok->value.strValue.c_str()
                );
                return nullptr;
            }
            return make_shared<PostfixOperatorExpr>(*this, ((FunctionType*)p->type)->getReturnType(),  (expr), p);
        }else{
            auto expr2 = parseExpr();
            if (!expr) {
                return nullptr;
            }
            if (p->position != OperatorInfo::infix) {
                scheato->logger()->FatalError(
                    getLocation(),
                    __FILE_NAME__,
                    __LINE__,
                    "%s is not infix operator.",
                    opTok->value.strValue.c_str()
                );
                return nullptr;
            }
            return make_shared<InfixOperatorExpr>(*this, ((FunctionType*)p->type)->getReturnType(),  (expr), p,  (expr2));
        }
    }
    return expr;
}
