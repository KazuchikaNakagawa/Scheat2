//
//  ScheatObjects.h
//  ProjectScheat
//
//  Created by かずちか on 2020/08/28.
//

#ifndef ScheatObjects_h
#define ScheatObjects_h
#include <string>
#include <vector>
#include <type_traits>
#include <iostream>
#include "ScheatToken.h"
#include "scheat.h"
#include "ScheatStd.hpp"

#define SV_P 18
namespace scheat {
class Token;
class ScheatLogManager;
class Scheat;
class ScheatLexer;
class ScheatDelegate;
namespace LegacyScheatParser {
extern void LLParse(ScheatLogManager *);
}

using namespace std;
using namespace scheatSTD;

struct DebugOption {
    bool enableDebug;
    bool developerMode;
};



/// represents a project file like CMakeLists.txt
class ScheatLogManager {
    bool debug;
    bool deepDebug;
    bool hasError;
    Scheat *scheato;
public:
    ScheatDelegate *delegate = nullptr;
    void logInfo(bool o) {
        debug = o;
    };
    void logAllInfo(bool b){
        deepDebug = b;
    };
    void FatalError(SourceLocation, const char *, unsigned int, const char *, ...) ;
    void Log(SourceLocation, const char *,unsigned int, const char *, ...);
    void Warning(SourceLocation, const char *,unsigned int, const char *, ...);
    void DevLog(SourceLocation, const char *,unsigned int, const char *, ...);
    ScheatLogManager(Scheat *sch);
    friend class Lexer;
    //friend void LegacyScheatParser::LLParse(ScheatLogManager *);
    friend class Scheat;
    friend class ScheatAnalyzer;
    friend class ScheatParser;
};

enum class ScheatError : int {
    ERR_node_has_illegal_value = -1,
    ERR_UNKNOWN = 0,
};


}

#endif /* ScheatObjects_h */
