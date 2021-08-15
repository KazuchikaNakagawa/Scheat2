#include "Parser.h"

#include "Nodes/AllNodes.h"

shared_ptr<IdentifierTerm>
Parser::parseAccessTerm(shared_ptr<IdentifierTerm> ptr, Type *ty){
    // id id
    if (tokens->kind == TokenKind::val_identifier) {
        string attribute = tokens->value.strValue;
        string cname = convert(ty);
        auto cinfo = global->getCInfo(cname);
        if (!cinfo) {
            scheato->logger()->FatalError(
                getLocation(),
                __FILE_NAME__,
                __LINE__,
                "type %s is undefined.",
                cname.c_str()
            );
            return nullptr;
        }
        auto pinfo = cinfo->getVInfo(attribute);
        if (!pinfo) {
            scheato->logger()->FatalError(
                getLocation(),
                __FILE_NAME__,
                __LINE__,
                "class %s has no attribute named %s",
                cname.c_str(),
                attribute.c_str()
            );
            return nullptr;
        }
        return make_shared<AccessTerm>(*this, pinfo->type,  (ptr), attribute,  pinfo->index);
    }
    return nullptr;
}

shared_ptr<IdentifierTerm>
Parser::parseFunctionCallTerm(shared_ptr<IdentifierTerm> ptr){
    if (!ptr->type->isFunctionTy()) {
        scheato->logger()->FatalError(
            getLocation(),
            __FILE_NAME__,
            __LINE__,
            "%s is not a function",
            ptr->name.c_str()
        );
        return nullptr;
    }
    // ( <- skip
    eat();
    FunctionType *ft = (FunctionType *)ptr->type;
    vector<Type *> args = ft->params();
    auto argExpr = make_shared<ArgumentExpr>(*this);
    int idx = 0;
    while (tokens->kind != TokenKind::tok_paren_r) {
        // expr, expr
        auto expr = parseExpr();
        if (!expr) {
            return nullptr;
        }
        if (args.size() < idx) {
            scheato->logger()->FatalError(
                getLocation(),
                __FILE_NAME__,
                __LINE__,
                "function requires %d arguments",
                args.size()
            );
            return nullptr;
        }
        if (args[idx] != expr->type) {
            scheato->logger()->FatalError(
                getLocation(),
                __FILE_NAME__,
                __LINE__,
                "%d argument requires %s type value but given %s",
                idx+1, convert(args[idx]).c_str(), convert(expr->type).c_str()
            );
            return nullptr;
        }
        ArgumentExpr::addArgument(*this, argExpr,  (expr));
        idx++;
        if (tokens->kind == TokenKind::tok_comma) {
            // , <- skip
            eat();
        }else{
            // next must be )
            break;
        }
    }
    if (args.size() != idx) {
        scheato->logger()->FatalError(
            getLocation(),
            __FILE_NAME__,
            __LINE__,
            "function requires %d arguments",
            args.size()
        );
        return nullptr;
    }
    if (tokens->kind != TokenKind::tok_paren_r) {
        scheato->logger()->FatalError(
            getLocation(),
            __FILE_NAME__,
            __LINE__,
            "expected ')'"
        );
        return nullptr;
    }
    eat();
    return make_shared<CallTerm>(*this, ft->getReturnType(), getLocation(), ptr,  (argExpr));
}

shared_ptr<IdentifierTerm>
Parser::parseIdentifierTerm(){
    shared_ptr<IdentifierTerm> ptr;
     Variable *info = nullptr;
    if (tokens->kind == TokenKind::val_identifier) {
        auto tok = tokens;
        string name = tokens->value.strValue;
        eat();
        info = currentContext->getVInfo(name);
        if (!info) {
            scheato->logger()->FatalError(
                getLocation(),
                __FILE_NAME__,
                __LINE__,
                "%s is undefined.",
                name.c_str()
            );
            return nullptr;
        }
        tok->value.strValue = info->name;
        ptr = make_shared<IdentifierTerm>(*this, info->type(), tok);
    }

    if (tokens->kind == TokenKind::tok_paren_l) {
        ptr = parseFunctionCallTerm( (ptr));
    }

    if (tokens->kind == TokenKind::val_identifier) {
        return parseAccessTerm((ptr), info->type());
    }
    return ptr;
}

void Parser::includeFoundation(){

}
