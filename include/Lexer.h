//
//  Lexer.hpp
//  scheat
//
//  Created by かずちか on 2020/07/31.
//

#ifndef Lexer_hpp
#define Lexer_hpp

#include <stdio.h>
#include <fstream>
#include "ScheatObjects.h"
#include "ScheatToken.h"
//#include "Classes.h"
#include "ScheatStd.h"

using namespace std;
namespace scheat {
class Scheat;
using namespace scheatSTD;

enum LexerState {
    commentState,
    longCommentState,
    numberState,
    doubleState,
    stringState,
    identifierState,
    operatorState,
    initState,
    ErrorState,
};

class Lexer {
    string buf;
    LexerState state;
    SourceLocation location;
    Token *tokens = nullptr;
    void input(int c, int next);
    void genTok();
    void addEOFToken();
    int commentDepth;
    bool skipFlag;
    bool isPossibleForPPPTok = false;
    bool AccessTokFlag = false;
    Scheat *scheato;
public:

    // initializer
    // Scheat object for version management
    Lexer(scheat::Scheat*);

    // lex(ifstream)
    // lex file and return token
    void lex();

    void lex(string);

    //static Token *lexString(Scheat *, string);
    //__deprecated
    //static Token *lexThis(Scheat *);
    //void lex(Scheat *sch) {
        //lexThis(sch);
    //};
    Token * getNextTok();
    Token * eatThisTok();
    // this function has fatal probrem
    // void addToken();
    void clear();

    void clearTokens() ;

    Token *getTokens();
};

}

#endif /* Lexer_hpp */
