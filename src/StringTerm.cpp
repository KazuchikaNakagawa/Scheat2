#include "Nodes/StringTerm.h"
using namespace nodes;

Value *StringTerm::fcodegen(){
    auto p = parser.strings.find(value);
    if (p == parser.strings.end()){
        auto gv = parser.builder.CreateGlobalString(value);
        parser.strings[value] = gv;
        return gv;
    }else{
        return parser.strings[value];
    }
    return nullptr;
}
