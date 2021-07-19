#ifndef STRINGTERM
#define STRINGTERM

#include "Term.h"

namespace nodes {
class StringTerm : public Term {
    string value = "";
public:
    virtual Value *codegen() override;
    virtual ~StringTerm(){};
    StringTerm(Parser &p, Token *tok)
    : Term(p,tok->location){
        value = tok->value.strValue;
        type = getStructures()["String"];
    }
};
}

#endif
