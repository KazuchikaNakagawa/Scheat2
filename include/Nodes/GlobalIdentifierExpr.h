#ifndef GLOBALIDENTIFIER
#define GLOBALIDENTIFIER

#include "IdentifierTerm.h"

namespace nodes {

class GlobalIdentifierExpr : public IdentifierTerm {
public:
    Type *spaceType;
    bool isConst;
    Value *fcodegen() override {
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
        auto gv = new GlobalVariable(
            *parser.module,
            spaceType,
            isConst,
            GlobalVariable::LinkageTypes::InternalLinkage,
            nullptr,
            name
        );
        parser.globalNamedValues[name] = gv;
        return gv;
    }
    virtual ~GlobalIdentifierExpr() {};
    GlobalIdentifierExpr(
        Parser &p,
        SourceLocation l,
        string n,
        Type *t = nullptr,
        bool isC = false
    )
    : IdentifierTerm(p, l)
    {
        name = n;
        spaceType = t;
        if (!t) type = t->getPointerTo();
        isConst = isC;
    }
};

} /* nodes */

#endif
