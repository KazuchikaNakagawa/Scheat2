//
//  ScheatStd.cpp
//  ScheatDebugger
//
//  Created by かずちか on 2021/04/01.
//

#include "ScheatStd.h"

using namespace scheatSTD;

SourceLocation SourceLocation::OUTOFFILE = SourceLocation(0, 0);

string SourceLocation::to_string() const{
    if (line == 0) {
        return "ScheatCompiler";
    }
    return ("line" + std::to_string(line) + "." + std::to_string(column));
}
