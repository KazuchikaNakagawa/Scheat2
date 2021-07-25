#ifndef IDENTIFIERTERM
#define IDENTIFIERTERM

#include "Term.h"

namespace nodes{
class IdentifierTerm : public Term {
    string name;
public:
    Value *codegen() override{
        auto v = parser.namedValues[name];
        if (v == nullptr){
            scheato->logger()->FatalError(location,
                __FILE_NAME__,
                __LINE__,
                "SystemError: %s is undefined in temporary namedValues", name.c_str());
            return nullptr;
        }
        return v;
    };
    virtual ~IdentifierTerm(){};
    IdentifierTerm(
        Parser &p,
        Type *t,
        Token *tok
    )
    : Term (p, tok->location)
    {
        type = t;
        name = tok->value.strValue;
    };
};
}
#endif
