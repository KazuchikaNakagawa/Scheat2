#ifndef GENERATOR
#define GENERATOR

#include "Parser.h"

namespace scheat{

using namespace llvm;
using namespace std;
class Generator {

public:
    unique_ptr<Module> generateFoundationModule();
};

}

#endif
