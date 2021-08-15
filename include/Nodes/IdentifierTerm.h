#ifndef IDENTIFIERTERM
#define IDENTIFIERTERM

#include "Term.h"

namespace nodes{
class IdentifierTerm : public Term {
public:
    string name;
    Value *fcodegen() override{
        auto v = parser.namedValues[name];
        if (v == nullptr) {
            parser.globalNamedValues[name];
        }
        if (v == nullptr){
            scheato->logger()->FatalError(location,
                __FILE_NAME__,
                __LINE__,
                "SystemError: %s is undefined in temporary namedValues", name.c_str());
            return nullptr;
        }
        return v;
    };
    virtual string to_string(){
        return name;
    }
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
    IdentifierTerm(Parser &p, SourceLocation l): Term(p,l){};
};

class AccessTerm : public IdentifierTerm {
public:
    shared_ptr<IdentifierTerm> value;
    int index;
    Value *fcodegen() override{
        return parser.builder.CreateStructGEP(type, value->codegen(), index);
    };
    virtual ~AccessTerm(){};
    AccessTerm(
        Parser &p,
        Type *t,
        shared_ptr<IdentifierTerm> ptr,
        string name,
        int idx
    )
    : IdentifierTerm(p, ptr->location)
    {
        index = idx;
        value =  (ptr);
        type = t;
        this->name = name;
    }
    string to_string() override{
        return parser.convert(type) + "_" + name;
    };
};
}
#endif
