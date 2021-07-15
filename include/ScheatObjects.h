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
class _Scheat;
class Scheat;
class ScheatLexer;
class ScheatDelegate;
namespace LegacyScheatParser {
extern void LLParse(_Scheat *);
}

using namespace std;
using namespace scheatSTD;

struct DebugOption {
    bool enableDebug;
    bool developerMode;
};

namespace nodes2{

class DataHolder;

};

using namespace nodes2;

/// represents a project file like CMakeLists.txt
class _Scheat {
    bool debug;
    bool deepDebug;
    bool hasError;
    bool delLL;
    bool onlyAssembles = false;
    bool logTopString = false;
public:
    /// returns true if this fails to compile.
    /// this is regarded as a flag.
    bool hasProbrem() const { return hasError; };
    
    /// location to be compiled
    SourceLocation location;
    scheat::Token *tokens;
    std::string sourceFile = "";
    std::string targettingFile;
    std::string outputFilePath;
    std::string target;
    std::string datalayout;
    vector<std::string> header_search_path;
    vector<std::string> library_names;
    std::string loggingFile = "";
    std::string productName;
    ScheatDelegate *delegate = nullptr;
    void logInfo(bool o) {
        debug = o;
    };
    bool logsTopString() { return logTopString; };
    bool deletesLLFile() { return delLL; };
    bool getDebugSetting() {return debug;};
    void logAllInfo(bool b){
        deepDebug = b;
    };
    bool onlyAsm() {return onlyAssembles;};
    template<class Lxr = ScheatLexer> void lex(){
        if (is_base_of<Lxr, ScheatLexer>::value){
            Lxr::lex(this);
        }
    };
    void FatalError(SourceLocation, const char *, unsigned int, const char *, ...) ;
    void Log(SourceLocation, const char *,unsigned int, const char *, ...);
    void Warning(SourceLocation, const char *,unsigned int, const char *, ...);
    void DevLog(SourceLocation, const char *,unsigned int, const char *, ...);
    _Scheat();
    _Scheat(Scheat *sch);
    void include(string filename) { Warning(SourceLocation(), __FILE_NAME__, __LINE__, "this feature is not available yet."); };
    friend class Lexer;
    friend void LegacyScheatParser::LLParse(_Scheat *);
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
