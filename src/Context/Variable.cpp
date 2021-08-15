#include "Context/Variable.h"
#include "Parser.h"
#include "Nodes/AllNodes.h"
#include <vector>

using namespace scheat;
Variable *Variable::create(LocalContext *c, string name, Type *t, bool isConst, AccessState state){
    auto info = new  Variable(c->parser);
    info->isConst = isConst;
    info->_type = t;
    info->isFunction = false;
    info->accessState = state;
    info->c = c;
    info->name = c->prefix + "_" + name;
    if (!t) {
        info->typeDefined = false;
        info->value = make_shared<NewIdentifierExpr>(info->c->parser, info->c->parser.getLocation(), info->name, info->_type, isConst);
    }else{
        info->typeDefined = true;
        info->value = make_shared<NewIdentifierExpr>(info->c->parser, info->c->parser.getLocation(), info->name, info->_type, isConst);
    }
    info->isGlobal = false;
    c->locals[name] = info;
};

Variable *Variable::create(GlobalContext *c, string name, Type *t, bool isConst, AccessState state){
    auto info = new  Variable(c->parser);
    info->isConst = isConst;
    info->_type = t;
    info->isFunction = false;
    info->accessState = state;
    info->c = c;
    info->name = c->prefix + "_" + name;
    if (!t) {
        info->typeDefined = false;
        info->value = make_shared<GlobalIdentifierExpr>(info->c->parser, info->c->parser.getLocation(), info->name, info->_type, isConst);
    }else{
        info->typeDefined = true;
        info->value = make_shared<GlobalIdentifierExpr>(info->c->parser, info->c->parser.getLocation(), info->name, info->_type, isConst);
    }
    c->globals[name] = info;
    info->isGlobal = true;
};

Variable *Variable::create(GlobalContext *c, string name, Type *return_type, vector<Type *> argTypes, AccessState state, bool defined){
    auto info = new  Variable(c->parser);
    info->isConst = true;
    info->isFunction = false;
    info->accessState = state;
    info->c = c;
    info->name = c->prefix + "_" + name;
    info->isDefined = defined;
    if (!return_type) {
        info->_type = FunctionType::get(c->parser.builder.getVoidTy(), argTypes, false);
        info->types = argTypes;
        info->typeDefined = false;
    }else{
        info->typeDefined = true;
        info->_type = FunctionType::get(return_type, argTypes, false);
        info->types = argTypes;

        if (defined) info->value = make_shared<FunctionDeclareStatement>(c->parser, c->parser.getLocation(), name, info->type);
        if (!defined) info->value = make_shared<ExternalFunctionStatement>(c->parser, c->parser.getLocation(), name, info->type);

        /// TODO
        //info->value = make_shared<GlobalIdentifierExpr>(info->c->parser, info->c->parser.getLocation(), info->name, info->_type, isConst);
    }
    c->globals[name] = info;
    info->isGlobal = true;
};


void Variable::setType(Type *t){
    if (_type->isFunctionTy()) {
        // TODO cast
        if (typeDefined) {
            parser.scheato->logger()->FatalError(
                parser.getLocation(),
                __FILE_NAME__,
                __LINE__,
                "already defined as %s", parser.convert(_type).c_str()
            );
            return;
        }
        if ((FunctionType *)_type->getReturnType() != parser.builder.getVoidTy()) {
            parser.scheato->logger()->FatalError(
                parser.getLocation(),
                __FILE_NAME__,
                __LINE__,
                "already defined as %s", convert(_type).c_str()
            );
            return;
        }
        _type = FunctionType::get(c->parser.builder.getVoidTy(), argTypes, false)
        typeDefined = true;
        if (defined) value = make_shared<FunctionDeclareStatement>(c->parser, c->parser.getLocation(), name, type);
        if (!defined) value = make_shared<ExternalFunctionStatement>(c->parser, c->parser.getLocation(), name, type);
    }

    if (_type != nullptr) {
        parser.scheato->logger()->FatalError(
            parser.getLocation(),
            __FILE_NAME__,
            __LINE__,
            "already defined as %s", convert(_type).c_str()
        );
        return;
    }
    _type = t;
    typeDefined = true;

    value->type = _type;
}

void Variable::addBody(shared_ptr<Statement> s){
    if (!isFunction) {
        parser.scheato->logger()->FatalError(
            parser.getLocation(),
            __FILE_NAME__,
            __LINE__,
            "cannot add body to function"
        );
        return;
    }
    if (isDefined) {
        parser.scheato->logger()->FatalError(
            parser.getLocation(),
            __FILE_NAME__,
            __LINE__,
            "cannot add body to defined function"
        );
        return;
    }
}

shared_ptr<Term> Variable::loaded(){
    if (isFunction) {
        parser.scheato->logger()->FatalError(
            parser.getLocation(),
            __FILE_NAME__,
            __LINE__,
            "cannot load function"
        );
        return nullptr;
    }
    return make_shared<LoadExpr>(parser, value);
}

void Variable::assign(shared_ptr<Expr> value){
    if (value->type != _type) {
        parser.scheato->logger()->FatalError(
            parser.getLocation(),
            __FILE_NAME__,
            __LINE__,
            "already defined as %s", parser.convert(_type).c_str()
        );
        return;
    }
    if (isFunction ) {
        parser.scheato->logger()->FatalError(
            parser.getLocation(),
            __FILE_NAME__,
            __LINE__,
            "cannot assign to function"
        );
        return;
    }
    c->statements.push_back(make_shared<AssignStatement>(parser, this->value, value));
}
