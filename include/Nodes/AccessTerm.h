#ifndef ACCESSTERM
#define ACCESSTERM

#include "IdentifierTerm.h"

namespace nodes{

// class AccessTerm : public Term {
//     shared_ptr<Term> lhs;
//     int index;
// public:
//     Value *codegen() override{
//         auto value = lhs->codegen();
//         auto ivalue = parser.builder.getInt32(index);
//         return parser.builder.CreateGEP(type, value, ivalue);
//     }
//     virtual ~AccessTerm(){};
//     AccessTerm(
//         Parser &p,
//         Type *t,
//         shared_ptr<Term> lvalue,
//         int i
//     )
//     : Term(p, lvalue->location)
//     {
//         type = t;
//         index = i;
//         lhs =  (lvalue);
//     }
// };

}

#endif
