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
#include "ScheatContextStructures.h"
#include "scheatPriv.hpp"
#include "ScheatStatics.h"
#include "ScheatContext.h"
#include "Lexer.hpp"
#include "Classes.h"
#include "ScheatAST.hpp"
#include "ScheatEncoder.h"
#include "Utilities.h"

using namespace scheat;


bool Scheat::hasProbrem() const{
    return schobj->hasProbrem();
}

void _Scheat::FatalError(SourceLocation location, const char *fn, unsigned int line, const char *fmt, ...){
    hasError = true;
    FILE *fp = stdout;
    if (loggingFile != "") {
        fp = fopen(loggingFile.c_str(), "a");
        if (!fp) {
            printf("logging file couldn't be opened.");
        }
    }
    if (delegate != nullptr) {
        delegate->fatalError(this,location, targettingFile, fmt);
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

void _Scheat::Warning(SourceLocation location, const char *fn, unsigned int line, const char *format, ...){
    if (delegate != nullptr) {
        delegate->warning(this, location, sourceFile, format);
        return;
    }
    if (deepDebug) {
        printf("\033[1;43mWarning:\033[m(from %s, line%u)\n in file: %s\n line%u.%u : ",
               fn,
               line,
               targettingFile.c_str(),
               location.line,
               location.column);
    }else{
        printf("\033[1;43mWarning:\033[m\n in file: %s\n line%u.%u : ",
               targettingFile.c_str(),
               location.line,
               location.column);
    }
    va_list arg;
    
    va_start(arg, format);
    ::vprintf(format, arg);
    va_end(arg);
    printf("\n");
}

void _Scheat::Log(SourceLocation location, const char *fn, unsigned int line, const char *fmt, ...){
    if (!debug) {
        return;
    }
    if (delegate != nullptr) {
        delegate->log(this, location, targettingFile, fmt);
        return;
    }
    if (deepDebug) {
        printf("\033[1mLog:\033[m(from %s, line%u)\n in file: %s\n line%u.%u : ",
               fn,
               line,
               targettingFile.c_str(),
               location.line,
               location.column);
    }else{
        printf("\033[1mLog:\033[m\n in file: %s\n line%u.%u : ",
               targettingFile.c_str(),
               location.line,
               location.column);
    }
    va_list arg;
    
    va_start(arg, fmt);
    ::vprintf(fmt, arg);
    va_end(arg);
    printf("\n");
}

_Scheat::_Scheat(){
    debug = false;
    deepDebug = false;
    hasError = false;
    targettingFile = "";
    location = SourceLocation();
    delegate = nullptr;
}

_Scheat::_Scheat(Scheat *sch){
    debug = sch->debug;
    deepDebug = sch->deepDebug;
    sch->schobj = this;
    sourceFile = sch->sourceFile;
    targettingFile = sch->targettingFile;
    outputFilePath = sch->outputFilePath;
    target = sch->target;
    datalayout = sch->datalayout;
    header_search_path = sch->header_search_path;
    library_names = sch->library_search_path;
    delegate = sch->delegate;
    productName = sch->productName;
    onlyAssembles = sch->onlyAssemble;
    delLL = sch->deletesIRFiles;
    logTopString = sch->logTopString;
    tokens = nullptr;
}

void Scheat::ready(){
    scheato = new _Scheat(this);
    ScheatContext::Init(scheato);
    if (isMain) {
        ScheatContext::AddMain();
    }
}

void Scheat::addMore(){
    if (scheato == nullptr) {
        ready();
        return;
    }
    auto newone = new _Scheat(this);
    newone->tokens = scheato->tokens;
    scheato = newone;
    ScheatContext::Init(scheato);
    if (isMain) {
        ScheatContext::AddMain();
    }
}

Scheat::Scheat(){
    debug = false;
    deepDebug = false;
    targettingFile = "";
    delegate = nullptr;
    if (scheato != nullptr) {
        scheato->FatalError(SourceLocation(), __FILE_NAME__, __LINE__, "Another Scheat is initialized. One thread can have only one Scheat.");
        exit(0);
    }
//    scheato = new _Scheat(this);
//    ScheatContext::Init(scheato);
}

void _Scheat::DevLog(SourceLocation location, const char *fn, unsigned int line, const char *fmt, ...){
    if (deepDebug) {
        printf("\033[1mLog:\033[m(from %s, line%u)\n in file: %s\n line%u.%u : ",
               fn,
               line,
               targettingFile.c_str(),
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
