#pragma once
#include "chokolait.hpp"
#include "camera.hpp"
#include "player.hpp"
#include "weaponui.hpp"

CE_BEGIN_NAMESPACE

CE_SCRIPT_DEF(WeaponMaster) {
public:
    
    CE_SERIALIZABLE class WeaponInfo {
    public:
        CE_SERIALIZE bool targeted;
        CE_SERIALIZE float range;
        CE_SERIALIZE float angle;
    };
    
    CE_SERIALIZE std::vector<WeaponInfo> teet;
    
    CE_SERIALIZE float scanAngle;
    CE_SERIALIZE float maxScanDist;
    
    CE_SERIALIZE SceneObject camobj;
    
    Enemy target;
    
    CE_SERIALIZE WeaponUI ui;
    
    void OnStart() override {
        
    }
    
    void GetEnemy() {
        target = nullptr;
        const auto mypos = object()->transform()->worldPosition();
        const auto campos = camobj->transform()->worldPosition();
        const auto camfwd = camobj->transform()->forward();
        const auto cth = std::cos(scanAngle);
        
        auto objs = ChokoLait::scene->objects();
        SceneObject cobj = nullptr;
        float cdst = 1000000000000;
        for (auto& o : objs) {
            if (o->name()[0] == '>') {
                const auto dst = o->transform()->worldPosition() - campos;
                const auto dstl = dst.length();
                const auto cth2 = camfwd.dot(dst / dstl);
                if (cth2 < cth && dstl < cdst) {
                    cdst = dstl;
                    cobj = o;
                }
            }
        }
        
        if (!!cobj) {
            target = cobj->GetComponent<Enemy>();
        }
    }
    
    void Fire() {
        
    }
    
    void OnUpdate() override {
        GetEnemy();
        
        if (!!target) {
            if (Input::KeyDown(InputKey::LeftShift)) {
                Fire();
            }
            
            ui->target = target->object();
        }
        else {
            ui->target = nullptr;
        }
    }
};

CE_END_NAMESPACE
