#ifndef TERM
#define TERM

#include "PrimaryExpr.h"
namespace nodes{
class Term : public PrimaryExpr {
public:
    virtual Value *fcodegen() override{
        return nullptr;
    }
    virtual ~Term(){};
    Term(Parser &p, SourceLocation l) : PrimaryExpr(p,l){};
};
}
#endif
