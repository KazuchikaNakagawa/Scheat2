#include "Parser.h"
#include "Nodes/AllNodes.h"

shared_ptr<Expr> Parser::parseNewIdentifierExpr(){
    eat();
    string name;
    SourceLocation loc;
    while (true) {
        if (tokens->kind == TokenKind::val_identifier) {
            loc = tokens->location;
            name = tokens->value.strValue;
            eat();
            break;
        }
        else/* if (tokens->kind == tok_)*/{
            scheato->logger()->FatalError(
                tokens->location,
                __FILE_NAME__,
                __LINE__,
                "expected identifier token"
            );
        }
    }
    Type *type = nullptr;
    if (tokens->kind == TokenKind::tok_of) {
        eat();
        type = parseTypeExpr();
        if (!type) {
            return nullptr;
        }

    }

    /*
    if (tokens->kind == ) {

    }
    */
    auto v = Variable::create((LocalContext*)currentContext, name, type);
    ((LocalContext *)currentContext)->locals[name] = v;
    return v->getExpr();
}
