#ifndef PARSER
#define PARSER

#include "Lexer.h"
#include "ScheatObjects.h"
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

using namespace std;
using namespace llvm;

namespace scheat{

class Lexer;
class Scheat;

class Parser {
public:
    Scheat *scheato = nullptr;
    LLVMContext context;
    unique_ptr<Module> module;
    llvm::IRBuilder<> builder;
    Parser(Lexer *);
};

}
#endif
