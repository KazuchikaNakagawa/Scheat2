#include "Parser.h"
#include "Nodes/AllNodes.h"

shared_ptr<Expr> Parser::parseGlobalIdentifierExpr(){
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

    if (tokens->kind == TokenKind::tok_of) {
        eat();

    }

    /*
    if (tokens->kind == ) {

    }
    */
    auto v =  Variable::create(global, name, nullptr);

    global->globals[name] = v;
    return v->getExpr();
}
