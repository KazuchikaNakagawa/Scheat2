#ifndef FLOATTERM
#define FLOATTERM

#include "Term.h"

namespace nodes {

class FloatTerm : public Term {
    double value;
public:
    virtual Value *fcodegen() override{
        return ConstantFP::get(type, value);
    }
    virtual ~FloatTerm(){};
    FloatTerm(Parser &p, Token *tok)
    : Term(p, tok->location){
        value = tok->value.doubleValue;
        type = Type::getDoubleTy(p.context);
    }
};

}

#endif
