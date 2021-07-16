//
//  scheat.hpp
//  scheat
//
//  Created by かずちか on 2020/07/30.
//

#ifndef scheat_
#define scheat_
#include <string>
#pragma GCC visibility push(default)
#include "ScheatStd.hpp"
#include "Lexer.hpp"
namespace scheat{

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
    std::string productName;
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
    Scheat(string projectName) : projectName(projectName){};
    friend class ScheatLogManager;
};



class IRBuilder;

}

#pragma GCC visibility pop
#endif
