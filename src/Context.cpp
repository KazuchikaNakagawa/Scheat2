#include "Context.h"

 Variable* LocalContext::getVInfo(string key){
    auto p = locals.find(key);
    if (p == locals.end()) {
        if (base == nullptr) return nullptr;
        return base->getVInfo(key);
    }
    return p->second;
}

 Variable *GlobalContext::getVInfo(string key){
    auto p = globals.find(key);
    if (p == globals.end()) {
        return nullptr;
    }
    return p->second;
}

ClassInfo *GlobalContext::getCInfo(string key){
    auto p = classes.find(key);
    if (p == classes.end()) {
        return nullptr;
    }
    return p->second;
}

llvm::StructType *ClassInfo::getType(){
    vector<llvm::Type *> arr;
    for (auto pair : properties){
        arr.push_back(pair.second->type);
    }
    type->setBody(arr);
    return type;
}

PropertyInfo *ClassInfo::getVInfo(string key){
    auto p = properties.find(key);
    if (p == properties.end()) {
        return nullptr;
    }
    return p->second;
}

ClassInfo::ClassInfo(string name, LLVMContext &c){
    type = StructType::create(c, name);
}
