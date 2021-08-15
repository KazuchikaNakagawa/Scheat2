#include "Parser.h"
#include "Nodes/AllNodes.h"



shared_ptr<Statement>
Parser::parseExternalFunctionStatement(){

    // eat 'require'
    eat();

    // eat 'to'
    if (tokIs(TokenKind::tok_to)) {
        eat();
    }else{
        scheato->logger()->FatalError(
            getLocation(),
            __FILE_NAME__,
            __LINE__,
            "expected 'to' keyword.\nrequire to <name> (<argTypes...>) (return <Type>)."
        );
        return nullptr;
    }

    Token* idtok = nullptr;
    // get identifier
    if (tokIs(TokenKind::val_identifier)) {
        idtok = tokens;
        eat();
    }else{
        scheato->logger()->FatalError(
            getLocation(),
            __FILE_NAME__,
            __LINE__,
            "expected function name.\nrequire to <name> (<argTypes...>) (return <Type>)."
        );
        return nullptr;
    }

    // if there are 'with', eat
    if (tokIs(TokenKind::tok_with)) {
        eat();
    }

    // eat '('
    if (tokIs(TokenKind::tok_paren_l)) {
        eat();
    }else{
        scheato->logger()->FatalError(
            getLocation(),
            __FILE_NAME__,
            __LINE__,
            "expected '('"
        );
        return nullptr;
    }

    // get argTypes
    vector<Type *> argTypes = {};
    while (!tokIs(TokenKind::tok_paren_r)){
        auto type = parseTypeExpr();
        if (!type) {
            return nullptr;
        }
        argTypes.push_back(type);
    }
    if (tokIs(TokenKind::tok_paren_r)) {
        eat();
    }else{
        scheato->logger()->FatalError(
            getLocation(),
            __FILE_NAME__,
            __LINE__,
            "expected ')'\nrequire to <name> (<argTypes...>) (return <Type>)."
        );
        return nullptr;
    }

    // get return type
    if (tokIs(TokenKind::tok_paren_l)) {
        eat();
    }else{
        scheato->logger()->FatalError(
            getLocation(),
            __FILE_NAME__,
            __LINE__,
            "expected '('\nrequire to <name> (<argTypes...>) (return <Type>)."
        );
        return nullptr;
    }
    // eat return
    if (tokIs(TokenKind::tok_return)) {
        eat();
    }else{
        scheato->logger()->FatalError(
            getLocation(),
            __FILE_NAME__,
            __LINE__,
            "expected 'return' keyword.\nrequire to <name> (<argTypes...>) (return <Type>)."
        );
        return nullptr;
    }
    auto return_type = parseTypeExpr();
    if (!return_type) {
        return nullptr;
    }
    auto f = Variable::create(global, idtok->value.strValue, return_type, argTypes, s_public ,true);
    global->globals[idtok->value.strValue] = f;
    return make_shared<ExprStatement>(*this, f->getExpr());
}
