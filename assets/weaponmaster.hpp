#pragma once
#include "chokolait.hpp"

CE_BEGIN_NAMESPACE

CE_SCRIPT_DEF(WeaponMaster) {
public:
    
    CE_SERIALIZABLE class A {
    public:
        CE_SERIALIZE std::vector<float> x;
        CE_SERIALIZE int f;
    };
    
    CE_SERIALIZABLE class B {
    public:
        CE_SERIALIZE float y;
        CE_SERIALIZE std::vector<A> aa;
    };
    
    CE_SERIALIZE std::vector<B> teet;
    
    void OnStart() override {
        std::cout << "value is " << teet[1].aa[0].x[2] << std::endl;
    }
    void OnUpdate() override {
        
    }
};

CE_END_NAMESPACE
