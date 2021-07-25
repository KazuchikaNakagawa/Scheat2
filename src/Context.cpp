#include "Context.h"

VariableInfo* LocalContext::getVInfo(string key){
    auto p = locals.find(key);
    if (p == locals.end()) {
        if (base == nullptr) return nullptr;
        return base->getVInfo(key);
    }
    return &p->second;
}

VariableInfo *GlobalContext::getVInfo(string key){
    auto p = globals.find(key);
    if (p == globals.end()) {
        return nullptr;
    }
    return &p->second;
}

llvm::StructType *ClassInfo::getType(llvm::LLVMContext &c){
    vector<llvm::Type *> arr;
    for (auto pair : properties){
        arr.push_back(pair.second.type);
    }
    auto type = llvm::StructType::create(c);
    type->setBody(arr);
    return type;
}
