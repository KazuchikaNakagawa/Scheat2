//
//  scheat.cpp
//  scheat
//
//  Created by かずちか on 2020/07/30.
//

#include <iostream>
#include <stdio.h>
#include <cstdarg>
#include <fstream>
#include <filesystem>
#include "scheat.h"
#include "ScheatObjects.h"
#include "Utilities.h"

using namespace scheat;
using namespace std::__fs::filesystem;

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
        delegate->fatalError(this->scheato,location, scheato->targettingFile, fmt);
        return;
    }
    if (deepDebug) {
        fprintf(fp, "\033[1;31mError:\033[m(from %s, line%u)\n in file: %s\n line%u.%u : ",
               fn,
               line,
               scheato->targettingFile.c_str(),
               location.line,
               location.column);
    }else{
        fprintf(fp, "\033[1;31mError:\033[m\n in file: %s\n line%u.%u : ",
               scheato->targettingFile.c_str(),
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
    FILE *fp = stdout;
    if (loggingFile != "") {
        fp = fopen(loggingFile.c_str(), "a");
        if (!fp) {
            printf("logging file couldn't be opened.");
        }
    }
    if (delegate != nullptr) {
        delegate->warning(this->scheato, location, scheato->targettingFile, format);
        return;
    }
    if (deepDebug) {
        fprintf(fp,"\033[1;43mWarning:\033[m(from %s, line%u)\n in file: %s\n line%u.%u : ",
               fn,
               line,
               scheato->targettingFile.c_str(),
               location.line,
               location.column);
    }else{
        fprintf(fp,"\033[1;43mWarning:\033[m\n in file: %s\n line%u.%u : ",
               scheato->targettingFile.c_str(),
               location.line,
               location.column);
    }
    va_list arg;

    va_start(arg, format);
    ::vfprintf(fp,format, arg);
    va_end(arg);
    fprintf(fp, "\n");
}

void ScheatLogManager::Log(SourceLocation location, const char *fn, unsigned int line, const char *fmt, ...){
    if (!debug) {
        return;
    }
    FILE *fp = stdout;
    if (loggingFile != "") {
        fp = fopen(loggingFile.c_str(), "a");
        if (!fp) {
            printf("logging file couldn't be opened.");
        }
    }
    if (delegate != nullptr) {
        delegate->log(this->scheato, location, scheato->targettingFile, fmt);
        return;
    }
    if (deepDebug) {
        fprintf(fp,"\033[1mLog:\033[m(from %s, line%u)\n in file: %s\n line%u.%u : ",
               fn,
               line,
               scheato->targettingFile.c_str(),
               location.line,
               location.column);
    }else{
        fprintf(fp,"\033[1mLog:\033[m\n in file: %s\n line%u.%u : ",
               scheato->targettingFile.c_str(),
               location.line,
               location.column);
    }
    va_list arg;

    va_start(arg, fmt);
    ::vfprintf(fp,fmt, arg);
    va_end(arg);
    fprintf(fp,"\n");
}

ScheatLogManager::ScheatLogManager(Scheat *sch){
    debug = sch->debug;
    deepDebug = sch->deepDebug;
    delegate = sch->delegate;
    if (sch->projectName == ""){return;}
    ofstream ofs(sch->projectName + ".log");
    scheato = sch;
}

void Scheat::ready(){
    manager = new ScheatLogManager(this);
}

void Scheat::addMore(){
    if (manager == nullptr) {
        ready();
        return;
    }
    auto newone = new ScheatLogManager(this);
    manager = newone;
}

Scheat::Scheat(string projectName): projectName(projectName){
    debug = false;
    deepDebug = false;
    this->targettingFile = "";
    delegate = nullptr;
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

void Scheat::setProductName(string nm){
    if (nm == ""){ return; }
    outputFilePath = nm;
    auto fpath = path(nm);
    if (!fpath.has_extension() || fpath.extension() == ".o" || fpath.extension() == ".exe"){
        outputFileType = OutputFileTypes::objectFile;
    }else if (fpath.extension() == ".a"){
        outputFileType = OutputFileTypes::staticLibrary;
    }else{
        manager->FatalError(SourceLocation(),__FILE_NAME__,__LINE__, "result file is not suitable. choose file extension from .o, .a, .exe");
    }
}

void Scheat::complementSettings(){
    if (targetFiles.empty()) {
        printf("to complete settings, at least sourceFile is needed.");
        return;
    }

    if (outputFilePath == "") {
        outputFilePath = getFileName(targetFiles[0]);
    }

    if (projectName == "") {
        projectName = outputFilePath;
    }

}

void Scheat::logInfo(bool o){
    debug = o;
    if (manager != nullptr) manager->logInfo(o);
}

void Scheat::logAllInfo(bool b){
    deepDebug = b;
    if (manager != nullptr) manager->logAllInfo(b);
};
