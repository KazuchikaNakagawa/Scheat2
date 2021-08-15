#ifndef SCHEATCONTEXT
#define SCHEATCONTEXT

#include <llvm/IR/IRBuilder.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <string>
#include <map>
#include <vector>

using namespace std;
using namespace llvm;

namespace nodes {
    class Statement;
    class Term;
    class Expr;
} /* nodes */

namespace scheat {
enum AccessState {
    s_public = 1,
    s_private = -1,
    s_fileprivate = -2
};

class  Variable;

class PropertyInfo {
public:
    int index;
    llvm::Type *type;
    AccessState state;
    bool isFunction;
};

class OperatorInfo : public PropertyInfo {
public:
    enum Precidence {
        top,
        primary,
        secondary
    } precidence;
    enum Position{
        prefix,
        infix,
        postfix
    } position;
    string name;
};

class Parser;

class ClassInfo {
    StructType *type;
public:
    ClassInfo *baseInfo;
    map<string, PropertyInfo*> properties;
    map<string, OperatorInfo*> operators;
    llvm::StructType *getType();
    PropertyInfo *getVInfo(string key);
    ClassInfo(string, LLVMContext &);
};

class Context {
public:
    Parser &parser;
    vector<shared_ptr<nodes::Statement>> statements;
    // it shows also namespace
    string prefix = "";
    virtual  Variable *getVInfo(string){
        return nullptr;
    };
    Context(Parser &p) : parser(p){};
};

class LocalContext : public Context {
public:
    Context *base;
    map<string,  Variable*> locals;
    Variable *getVInfo(string) override;
    LocalContext(Parser &p) : Context(p){};
};

class GlobalContext : public Context {
public:
    map<string, ClassInfo*> classes;
    map<string,  Variable*> globals;
     Variable *getVInfo(string) override;
    ClassInfo *getCInfo(string);
    GlobalContext(Parser &p) : Context(p){};
};
}
using namespace scheat;
#endif
