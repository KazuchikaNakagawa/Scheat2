#ifndef BOOLTERM
#define BOOLTERM

#include "Term.h"

namespace nodes {

class BoolTerm : public Term {
    bool value;
public:
    virtual Value *fcodegen() override{
        if (value) {
            return parser.builder.getTrue();
        }else{
            return parser.builder.getFalse();
        }
        return nullptr;
    };
    virtual ~BoolTerm(){};
    BoolTerm(Parser& p, Token *tok)
    : Term(p, tok->location){
        value = tok->value.boolValue;
    }
};

} /*nodes */

#endif
