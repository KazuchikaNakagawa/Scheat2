#ifndef NEWIDENTIFIEREXPR
#define NEWIDENTIFIEREXPR

#include "Expr.h"
#include "../Context.h"

namespace nodes {

class NewIdentifierExpr : public Expr {
public:
    Type *spaceType;
    string name;
    bool isConst;
    Value *fcodegen() override{
        if (!spaceType) {
            if (!type) {
                scheato->logger()->FatalError(
                    location,
                    __FILE_NAME__,
                    __LINE__,
                    "SystemError: type is not specified."
                );
            }
            spaceType = type->getPointerElementType();
        }
        auto v = parser.builder.CreateAlloca(spaceType, nullptr, name);
        parser.namedValues[name] = v;
        return v;
    };
    virtual ~NewIdentifierExpr(){};
    NewIdentifierExpr(
        Parser &p,
        SourceLocation l,
        string n,
        Type *t = nullptr,
        bool isC = false
    )
    : Expr(p, l)
    {
        name = n;
        spaceType = t;
        if (!t) type = t->getPointerTo();
        isConst = isC;
    };

};

} /* nodes */

#endif
