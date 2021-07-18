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
class ScheatLogManager;
class Scheat;
class ScheatLexer;
class ScheatDelegate;

using namespace scheatSTD;

class ScheatLogManager;
using namespace std;
class Scheat;
class ScheatDelegate {
public:

    virtual void fatalError(Scheat *scheat,SourceLocation location, std::string filePath, std::string message, ...);

    virtual void warning(Scheat *scheat, SourceLocation location, std::string filePath, std::string message, ...);

    virtual void log(Scheat *scheat, SourceLocation location, std::string filePath, std::string message, ...);

    virtual std::string target_triple();

    virtual std::string datalayout();

};

class ScheatLogManager;

enum class OutputFileTypes{
    objectFile,
    staticLibrary,
    sharedLibrary
};

class Scheat {
    bool debug;
    bool deepDebug;
    ScheatLogManager *manager = nullptr;
    bool hasError = false;
public:
    string projectName;
    /// returns true if this fails to compile.
    /// this is regarded as a flag.
    bool hasProbrem() const;
    OutputFileTypes outputFileType = OutputFileTypes::staticLibrary;
    std::string targettingFile;
    std::string outputFilePath;
    std::string target;
    std::string datalayout;
    std::vector<string> targetFiles;
    vector<std::string> header_search_path;
    vector<std::string> library_search_path;
    vector<string> linkPaths = {};
    ScheatDelegate *delegate = nullptr;
    bool deletesIRFiles = true;
    bool onlyAssemble = false;
    bool logTopString = false;
    void complementSettings();
    void logInfo(bool o) ;
    void logAllInfo(bool b);
    void setProductName(std::string);
    void ready();
    void addMore();
    ScheatLogManager* logger(){ return manager; };
    Scheat(string projectName);
    friend class ScheatLogManager;
};



class IRBuilder;


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
    string loggingFile;
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
