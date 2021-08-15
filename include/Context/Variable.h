#ifndef  VARIABLE
#define  VARIABLE
#include "../Context.h"

namespace scheat {

using namespace nodes;
class PointerValue {
public:
    shared_ptr<Expr> value;
};

class Variable: public PointerValue {
    Variable(Parser &p) : parser(p) {};
    bool typeDefined = true;
    bool isGlobal = false;
    llvm::Type *_type = nullptr;
    Parser &parser;
    vector<Type *> types;
    bool isFunction = true;
    bool isDefined = false;
public:
    // this shows element type.
    Context *c;
    AccessState accessState = s_public;
    Type *type() const{
        return _type;
    };
    bool isConst = false;
    string name = "";
    void setType(Type *);
    void assign(shared_ptr<Expr>);
    unique_ptr<Term> loaded();
    void addBody(shared_ptr<Statement> s);
    shared_ptr<Expr> getExpr() {return value;};
    static Variable *create(LocalContext *c, string name, Type *t, bool isConst = false, AccessState state = s_public);
    static Variable *create(GlobalContext *c, string name, Type *t, bool isConst = false, AccessState state = s_public);
    static Variable *create(GlobalContext *c, string name, Type *return_type, vector<Type *> argTypes, AccessState state = s_public, bool defined = false);
};

}
#endif
