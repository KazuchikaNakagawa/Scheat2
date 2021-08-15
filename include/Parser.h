#ifndef PARSER
#define PARSER

#include "Lexer.h"
#include "ScheatObjects.h"
#include "Context.h"
#include "Context/Variable.h"
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/Linker/Linker.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/Host.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/TargetRegistry.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/Target/TargetOptions.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/LinkAllIR.h>
#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;
using namespace llvm;

namespace nodes {
    class Statement;
    class Expr;
    class NewIdentifierExpr;
    class Node;
    class IdentifierTerm;
    class GlobalIdentifierExpr;
    class PrimaryExpr;
    class CallTerm;
}

using namespace nodes;

namespace scheat{

class Lexer;
class Scheat;

class Parser {
public:
    Token *tokens;
    map<string, Type*> structures;
    string convertSecondary(string, Type *);
    void includeDefString();
    void includeString_init();
    void includePrint_String();
public:
    Context *currentContext;
    GlobalContext *global;
    map<string, GlobalVariable *> strings;
    // this is temporary and used in only generating
    map<string, Value *> namedValues;
    map<string, Value *> globalNamedValues;
    Scheat *scheato = nullptr;
    LLVMContext context;
    unique_ptr<Module> module;
    vector<shared_ptr<Statement>> statements;
    llvm::IRBuilder<> builder;
    Parser(Lexer *);
    friend class nodes::Node;
    void eat(){ tokens = tokens->next; };
    SourceLocation getLocation(){
        return tokens->location;
    }
    inline bool tokIs(TokenKind k)const {return tokens->kind == k;};
    bool isParsingGlobal() const{
        return currentContext == global;
    };
    void includeFoundation();
    bool nextIsValue();
    Type *parseTypeExpr();
    shared_ptr<Statement> parseStatement();
    shared_ptr<Expr> parseExpr();
    shared_ptr<Expr> parseOperatedExpr();
    shared_ptr<PrimaryExpr> parsePrimaryExpr();
    shared_ptr<IdentifierTerm> parseIdentifierTerm();
    shared_ptr<Expr> parseNewIdentifierExpr();
    shared_ptr<IdentifierTerm> parseAccessTerm(shared_ptr<IdentifierTerm>, Type*);
    shared_ptr<Expr> parseGlobalIdentifierExpr();
    shared_ptr<IdentifierTerm> parseFunctionCallTerm(shared_ptr<IdentifierTerm>);
    shared_ptr<Statement> parseExternalFunctionStatement();
    string convert(Type *);
    string demangle(Type *);
};

}

using namespace scheat;
#endif
