//
//  scheat.cpp
//  scheat
//
//  Created by かずちか on 2020/07/30.
//

#include <iostream>
#include <stdio.h>
#include <cstdarg>
#include "scheat.h"
#include "ScheatObjects.h"
#include "Utilities.h"

using namespace scheat;


bool Scheat::hasProbrem() const{
    return hasError;
}

void ScheatLogManager::FatalError(SourceLocation location, const char *fn, unsigned int line, const char *fmt, ...){
    scheato->hasError = true;
    FILE *fp = stdout;
    if (loggingFile != "") {
        fp = fopen(loggingFile.c_str(), "a");
        if (!fp) {
            printf("logging file couldn't be opened.");
        }
    }
    if (delegate != nullptr) {
        delegate->fatalError(this,location, scheato->targettingFile, fmt);
        return;
    }
    if (deepDebug) {
        fprintf(fp, "\033[1;31mError:\033[m(from %s, line%u)\n in file: %s\n line%u.%u : ",
               fn,
               line,
               targettingFile.c_str(),
               location.line,
               location.column);
    }else{
        fprintf(fp, "\033[1;31mError:\033[m\n in file: %s\n line%u.%u : ",
               targettingFile.c_str(),
               location.line,
               location.column);
    }
    va_list arg;

    va_start(arg, fmt);
    ::vfprintf(fp, fmt, arg);
    va_end(arg);
    fprintf(fp, "\n");
    fclose(fp);
    exit(9);
}

void ScheatLogManager::Warning(SourceLocation location, const char *fn, unsigned int line, const char *format, ...){
    if (delegate != nullptr) {
        delegate->warning(this, location, scheato->targettingFile, format);
        return;
    }
    if (deepDebug) {
        printf("\033[1;43mWarning:\033[m(from %s, line%u)\n in file: %s\n line%u.%u : ",
               fn,
               line,
               scheato->targettingFile.c_str(),
               location.line,
               location.column);
    }else{
        printf("\033[1;43mWarning:\033[m\n in file: %s\n line%u.%u : ",
               scheato->targettingFile.c_str(),
               location.line,
               location.column);
    }
    va_list arg;

    va_start(arg, format);
    ::vprintf(format, arg);
    va_end(arg);
    printf("\n");
}

void ScheatLogManager::Log(SourceLocation location, const char *fn, unsigned int line, const char *fmt, ...){
    if (!debug) {
        return;
    }
    if (delegate != nullptr) {
        delegate->log(this->scheato, location, scheato->targettingFile, fmt);
        return;
    }
    if (deepDebug) {
        printf("\033[1mLog:\033[m(from %s, line%u)\n in file: %s\n line%u.%u : ",
               fn,
               line,
               scheato->targettingFile.c_str(),
               location.line,
               location.column);
    }else{
        printf("\033[1mLog:\033[m\n in file: %s\n line%u.%u : ",
               scheato->targettingFile.c_str(),
               location.line,
               location.column);
    }
    va_list arg;

    va_start(arg, fmt);
    ::vprintf(fmt, arg);
    va_end(arg);
    printf("\n");
}

ScheatLogManager::ScheatLogManager(){
    debug = false;
    deepDebug = false;
    hasError = false;
    targettingFile = "";
    location = SourceLocation();
    delegate = nullptr;
}

ScheatLogManager::ScheatLogManager(Scheat *sch){
    debug = sch->debug;
    deepDebug = sch->deepDebug;
    delegate = sch->delegate;
    onlyAssembles = sch->onlyAssemble;
    tokens = nullptr;
}

void Scheat::ready(){
    manager = new ScheatLogManager(this);

    if (isMain) {
    }
}

void Scheat::addMore(){
    if (manager == nullptr) {
        ready();
        return;
    }
    auto newone = new ScheatLogManager(this);
    manager = newone;
}

Scheat::Scheat(){
    debug = false;
    deepDebug = false;
    targettingFile = "";
    delegate = nullptr;
    if (manager != nullptr) {
        manager->FatalError(SourceLocation(), __FILE_NAME__, __LINE__, "Another Scheat is initialized. One thread can have only one Scheat.");
        exit(0);
    }
//    scheato = new ScheatLogManager(this);
//    ScheatContext::Init(scheato);
}

void ScheatLogManager::DevLog(SourceLocation location, const char *fn, unsigned int line, const char *fmt, ...){
    if (deepDebug) {
        printf("\033[1mLog:\033[m(from %s, line%u)\n in file: %s\n line%u.%u : ",
               fn,
               line,
               scheato->targettingFile.c_str(),
               location.line,
               location.column);
        va_list arg;

        va_start(arg, fmt);
        ::vprintf(fmt, arg);
        va_end(arg);
        printf("\n");

    }else{
        return;
    }

}

void scheatPriv::HelloWorldPriv(const char * s)
{
    std::cout << s << std::endl;
};

void Scheat::setProductName(string nm){
    productName = nm;
    //schobj->productName = nm;
}

void ScheatLexer::lex(){
    lexer::Lexer lxr(scheato);
    lxr.lex(scheato);
    if (!scheato->tokens) {
        scheato->FatalError(SourceLocation(), __FILE_NAME__, __LINE__,
                            "Failed to lex and unable to continue.");
        exit(0);
    }
}

void ScheatLexer::testlex(std::string buf){
    lexer::Lexer lxr(scheato);
    lxr.lex(buf);
    lxr.getTokens()->enumerate();
}

void Scheat::complementSettings(){
    if (sourceFile == "") {
        printf("to complete settings, at least sourceFile is needed.");
        return;
    }

//    if (outputFilePath == "-") {
//        outputFilePath = getFileName(sourceFile);
//        delLL = true;
//    }else{
//        delLL = false;
//    }

    if (outputFilePath == "") {
        outputFilePath = getFileName(sourceFile);
    }

    if (productName == "") {
        productName = outputFilePath;
    }

    if (sourceFile.find(".scheat") != string::npos) {
        isMain = true;
    }
}

void Scheat::logInfo(bool o){
    debug = o;
    if (schobj != nullptr) schobj->logInfo(o);
}

void Scheat::logAllInfo(bool b){
    deepDebug = b;
    if (schobj != nullptr) schobj->logAllInfo(b);
};

void ScheatAnalyzer::parse(){
    if (scheato->deepDebug) {
        scheato->tokens->enumerate();
    }
    parser2::parse(scheato, scheato->tokens);
}

void ScheatEncoder::encode(){
    ofstream fp(scheato->outputFilePath + ".ll");
    if (!fp.is_open()) {
        scheato->FatalError(SourceLocation(), __FILE_NAME__, __LINE__, "%s could not  be opened.", scheato->outputFilePath.c_str());
        return;
    }
    ScheatContext::exportTo(fp);
    encoder::LLSCEncoder::encode(scheato->outputFilePath);
}

void ScheatEncoder::printout(){
    ScheatContext::printout();
}
