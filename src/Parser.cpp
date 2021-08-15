#include "Nodes/AllNodes.h"
#include "Context/Variable.h"
#include <string>
#include <vector>

Parser::Parser(Lexer *lxr) : tokens(lxr->getTokens()), builder(context) {
    scheato = lxr->scheato;

}

string Parser::convert(Type *t){
    string base = "";
    if (t->isPointerTy()){
        base += "the ";
        return convertSecondary(base, t->getPointerElementType());
    }
    return base;
}

string Parser::convertSecondary(string base, Type *t){
    if (t->isPointerTy()){
        if (base.find("the") == string::npos) {
            return convertSecondary(base + "the ", t->getPointerElementType());
        }else{
            return convertSecondary(base + " Pointer of ", t->getPointerElementType());
        }
    }
    if (t->isIntegerTy()) {
        return base + "Int";
    }
    if (t->isStructTy()) {
        auto type = (StructType *)t;
        string llname = type->getName().data();
        for (auto pair : global->classes) {
            if (pair.second->getType()->getName() == llname) {
                return base + pair.first;
            }
        }
    }
    if (t->isFunctionTy()) {
        FunctionType *ft = (FunctionType *)t;
        vector<Type *> args = ft->params();
        string types = " from(";
        int idx = 0;
        for (auto arg : args){
            types += convert(arg);
            idx++;
            if (args.size() > idx) {
                types += ", ";
            }
        }
        types += ")";
        return convert(ft->getReturnType()) + types;
    }
    return base;
}

bool Parser::nextIsValue(){
    if ((int)tokens->kind < 0 && -10 != (int)tokens->kind) {
        return true;
    }
    if (tokIs(TokenKind::tok_the)) {
        return true;
    }
    return false;
}

string Parser::demangle(Type *t){
    // the Int -> Pointer#Int
    if (t->isPointerTy()) {
        return "Pointer#"+demangle(t->getPointerElementType());
    }
    if (t->isIntegerTy()) {
        return "Int";
    }
    if (t->isStructTy()) {
        auto type = (StructType *)t;
        string llname = type->getName().data();
        for (auto pair : global->classes) {
            if (pair.second->getType()->getName() == llname) {
                return pair.first;
            }
        }
        scheato->logger()->FatalError(getLocation(), __FILE_NAME__, __LINE__, "unknown class %s", llname.c_str());
        return "";
    }
    // Int from(Int, Int) -> Int##Int##Int
    if (t->isFunctionTy()) {
        FunctionType *ft = (FunctionType *)t;
        vector<Type *> args = ft->params();
        string types = "##";
        int idx = 0;
        for (auto arg : args){
            types += convert(arg);
            idx++;
            if (args.size() > idx) {
                types += "##";
            }
        }
        return convert(ft->getReturnType()) + types;
    }
    return "";
}

void Parser::includeDefString(){
    auto cinfo = new ClassInfo("String", context);
    auto pinfo = new PropertyInfo();
    pinfo->index = 0;
    pinfo->type = builder.getInt8Ty()->getPointerTo();
    pinfo->isFunction = false;
    //pinfo->isConst = false;
    cinfo->properties["buf"] = pinfo;

    global->classes["String"] = cinfo;
}

void Parser::includeString_init(){
    std::vector<Type *> args = {builder.getInt8Ty()->getPointerTo()};
    auto fString_init = Variable::create(global, "String_init_pi8", global->classes["String"]->getType(), args);
    global->globals["String_init_Pointer#i8"] = fString_init;
}

void Parser::includePrint_String(){
    std::vector<Type *> args = {global->getCInfo("String")->getType()};
    auto fPrint_String = Variable::create(global, "print_String", builder.getVoidTy(), args);
    global->globals["print_String"] = fPrint_String;
}

// this will be obsoluted soon.
void Parser::includeFoundation(){
    includeDefString();
    includeString_init();
    //statements.push_back(make_shared<ExternalFunctionStatement>(*this, SourceLocation(), builder.getVoidTy(), "print_String", {global->getCInfo("String")->getType()}));
    //statements.push_back(make_shared<ExternalFunctionStatement>(*this, SourceLocation(), builder.getVoidTy(), "print_Int", {builder.getInt32Ty()}));

}
