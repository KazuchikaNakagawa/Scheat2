#ifndef INTTERM
#define INTTERM

#include "Term.h"
namespace nodes{
class IntTerm : public Term {
    int value;
public:
    virtual Value *fcodegen() override{
        return parser.builder.getInt32(value);
    }
    virtual ~IntTerm(){};
    IntTerm(Parser &p, Token *tok)
    : Term(p, tok->location){
        value = tok->value.intValue;
        type = Type::getInt32Ty(parser.context);
    }
};
}
#endif
