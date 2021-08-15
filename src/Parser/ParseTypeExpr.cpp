#include "Parser.h"
#include "Nodes/AllNodes.h"

Type *Parser::parseTypeExpr(){
    // id
    if (tokens->kind == TokenKind::val_identifier) {
        string name = tokens->value.strValue;
        auto cinfo = global->getCInfo(name);
        if (!cinfo) {
            scheato->logger()->FatalError(
                getLocation(),
                __FILE_NAME__,
                __LINE__,
                "unknown type %s appeared",
                name.c_str()
            );
            return nullptr;
        }
        eat();
        return cinfo->getType();
    }

    // the type
    if (tokens->kind == TokenKind::tok_the){
        eat();
        auto type = parseTypeExpr();
        if (type) {
            return type->getPointerTo();
        }
    }
    return nullptr;
};
