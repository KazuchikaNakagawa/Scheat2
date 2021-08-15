#include "Parser.h"
#include "Nodes/AllNodes.h"

template <typename U, typename T>
static shared_ptr<U> dynamic_unique_cast(std::shared_ptr<T>&& ptr) {
    return shared_ptr<U>(dynamic_cast<U*>(ptr.release()));
}

shared_ptr<Statement> Parser::parseStatement(){

    if (tokens->kind == TokenKind::tok_require) {

    }

    auto expr = parseExpr();
    if (!expr) {
        //scheato->logger()->FatalError(getLocation(), __FILE_NAME__, __LINE__,
        //"statement that starts %s is illegal." , tokens->to_string().c_str());
        return nullptr;
    }
    if (tokens->kind == TokenKind::tok_is){
        // assignmentStatement
        eat();
        auto rvalue = parseExpr();
        if (!rvalue) {
            return nullptr;
        }
        if (rvalue->type == Type::getVoidTy(context)) {
            scheato->logger()->FatalError(
                rvalue->location,
                __FILE_NAME__,
                __LINE__,
                "cannot assign void type value."
            );
            return nullptr;
        }
        if (expr->type == nullptr) {
            auto casted = dynamic_pointer_cast<NewIdentifierExpr>(expr);
            auto info = currentContext->getVInfo(casted->name);
            info->setType(rvalue->type);
            casted->type = rvalue->type->getPointerTo();
            expr =  (casted);
        }else{
            // going to be casted in the future
            if (expr->type != rvalue->type->getPointerTo()) {
                scheato->logger()->FatalError(getLocation(),
                                    __FILE_NAME__,
                                    __LINE__,
                                    "variable defined type %s, but assigned %s value.",
                                    convert(expr->type).c_str(),
                                    convert(rvalue->type).c_str());
                return nullptr;
            }
        }

        return make_shared<AssignStatement>(*this,  (expr),  (rvalue));
    }
    return nullptr;
}
