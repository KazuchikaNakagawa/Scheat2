#include "Nodes/Node.h"
#include "Parser.h"
using namespace nodes;
using namespace llvm;
using namespace std;

using namespace scheat;
Node::Node(Parser &p, SourceLocation l) : parser(p), type(Type::getVoidTy(p.context)){
    scheato = p.scheato;
    location = l;
}
