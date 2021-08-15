#ifndef GENERATOR
#define GENERATOR

#include <iostream>
namespace llvm {
    class Module;
} /* llvm */

namespace scheat{

using namespace llvm;
using namespace std;
class Generator {

public:
    unique_ptr<Module> generateFoundationModule();
};

}

#endif
