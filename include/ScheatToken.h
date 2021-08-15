//
//  ScheatToken.h
//  ProjectScheat
//
//  Created by かずちか on 2020/12/13.
//

#ifndef ScheatToken_h
#define ScheatToken_h
#include <string>
#include "ScheatStd.h"

namespace scheat {

using namespace scheatSTD;

//struct __deprecated SourceLocation {
//    SourceLocation(int l = 1, int c = 0) : line(l), column(c){};
//    int line;
//    int column;
//    ~SourceLocation() = default;
//    static SourceLocation OUTOFFILELOCATION;
//};

enum class TokenKind : int {

    tok_EOF = -10,

    val_identifier = -9,
    val_num = -8,
    val_str = -7,
    val_double = -6,
    val_bool = -5,
    val_operator = -4,
    val_null = -3,

    tok_this = 0,
    tok_the,
    tok_is,
    tok_of,
    tok_period,
    tok_comma,
    tok_range,
    tok_if,
    tok_for,
    tok_from,
    tok_times,
    tok_do,
    tok_done,
    tok_or,
    tok_paren_l,
    tok_paren_r,
    tok_brace_l,
    tok_brace_r,
    tok_access,
    tok_external,
    tok_require,
    tok_import,
    tok_export,
    tok_to,
    tok_with,
    tok_while,
    tok_loaded,
    tok_return,
    tok_break,
    tok_class,
    tok_its,

    tok_local,
    tok_global,

    embbed_func_print,
    embbed_func_import,
    embbed_func_free,
    embbed_func_assemble,
};

union TokenValue {
    std::string strValue;
    int intValue;
    bool boolValue;
    double doubleValue;
    TokenValue(){
        doubleValue = 0.0;
    }
    ~TokenValue(){

    }
    TokenValue(TokenValue &&){

    }
    TokenValue(const TokenValue &){

    }
};

class ScheatLogManager;

/// Token --Scheat's token.
struct Token {
    /// Token has chain structure

    // next : next Token pointer
    Token *next;

    // prev : previous Token pointer
    Token *prev;

    // TokenKind : presents type of Token.
    TokenKind kind;

    // TokenValue: value has 4 types.
    // scheat.int (llvm i32)
    // scheat.str (llvm i8*) or (llvm %scheatstd.string)
    // scheat.bool (llvm i1)
    // scheat.double (llvm double)
    TokenValue value;

    // last : returns last token
    Token *last();

    // first : returns first token
    Token *first();

    // location: SourceLocation
    // column , line
    SourceLocation location;
    void valInt(std::string);
    void valStr(std::string);
    void valBool(std::string);
    void valDouble(std::string);
    static Token *add(Token *, Token *);
    void enumerate(ScheatLogManager *);
    std::string encodeOperator(ScheatLogManager *);
    void out(ScheatLogManager *);
    string to_string(ScheatLogManager *) const;
    Token(){
        next = nullptr;
        prev = nullptr;
        kind = TokenKind::val_num;
        value.intValue = 0;
        location = SourceLocation();
    }
    void release(){

        if (prev != nullptr) {
            prev->release();
            prev = nullptr;
        }
        delete this;
    }
    Token(Token &&) : location(SourceLocation::OUTOFFILE) {};
    Token(const Token &) : location(SourceLocation::OUTOFFILE) {};
};

extern void eatThis(Token *&);

class Tokens {
    Token *tokens;
    Token *seek_ptr;
public:
    Token *ptr() { return seek_ptr; };
    void skip();
    void back();
    Tokens *operator += (Token *rhs){
        rhs->prev = this->tokens->last();
        this->tokens->last()->next = rhs;
        tokens = tokens->next;
        return this;
    };
    Token *operator[](unsigned int index){
        Token *t = tokens->first();
        for (int i = 0; i != index; i++) {
            t = t->next;
        }
        return t;
    };
};

}

#endif /* ScheatToken_h */
