#ifndef NODE
#define NODE

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
#include "../ScheatStd.h"
#include "ScheatObjects.h"
#include <map>
#include <string>
#include <vector>

using namespace scheat;
using namespace llvm;
using namespace scheatSTD;
using namespace std;
namespace nodes{

class Node {
public:
    Scheat *scheato = nullptr;
    Parser &parser;
    SourceLocation location;
    Type *type;

    Node(Parser &, SourceLocation);
    virtual Value *codegen(){ return nullptr; };
    virtual ~Node(){};
    map<string, Type *>& getStructures(){
        return parser.structures;
    };
};

};

#endif
