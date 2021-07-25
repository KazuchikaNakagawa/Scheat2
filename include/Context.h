#ifndef SCHEATCONTEXT
#define SCHEATCONTEXT

#include <llvm/IR/IRBuilder.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <string>
#include <map>
#include <vector>

using namespace std;
enum AccessState {
    s_public,
    s_private,
    s_fileprivate
};

class VariableInfo {
public:
    llvm::Type *type;
    AccessState accessState;
    bool isConst;
};

class OperatorInfo {
public:
    llvm::Type *type;
    string func_name;
};

class PropertyInfo {
public:
    int index;
    llvm::Type *type;
    AccessState state;
};

class ClassInfo {
public:
    ClassInfo *baseInfo;
    map<string, PropertyInfo> properties;
    llvm::StructType *getType(llvm::LLVMContext &);
};

class Context {
public:
    virtual VariableInfo *getVInfo(string){
        return nullptr;
    };
};

class LocalContext : public Context {
public:
    Context *base;
    map<string, VariableInfo> locals;
    VariableInfo *getVInfo(string) override;
};

class GlobalContext : public Context {
public:

    map<string, VariableInfo> globals;
    VariableInfo *getVInfo(string) override;
};

#endif
