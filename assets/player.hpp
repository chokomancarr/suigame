#pragma once
#include "chokolait.hpp"
#include "camera.hpp"

CE_BEGIN_NAMESPACE

CE_SCRIPT_DEF(Ppl) {
public:
    CE_SERIALIZE float moveSp;
    CE_SERIALIZE SceneObject camAxis;
    CE_SERIALIZE AnimClip idleClip;
    CE_SERIALIZE AnimClip runClip;
    
    CE_SERIALIZE float rotSp;

    pTransform tr;
    Animator anim;
    
    Cam camscr;
    
    float rottar = 180.f;
    
    void setclip(const AnimClip& c) {
        if (anim->clip() != c) {
            anim->clip(c);
        }
    }
    
    void OnStart() override {
        tr = object()->transform();
        anim = object()->children()[0]->GetComponent<Animator>();
        anim->single(true);
        anim->repeat(true);
        
        camscr = camAxis->children()[0]->GetComponent<Cam>();
    }
    void OnUpdate() override {
        bool iw = Input::KeyHold(InputKey::W);
        bool ia = Input::KeyHold(InputKey::A);
        bool is = Input::KeyHold(InputKey::S);
        bool id = Input::KeyHold(InputKey::D);
        if (iw || ia || is || id) {
            float angle = iw ? 0.f : 180.f;
            if (ia) angle = 90.f;
            if (id) angle = iw ? -90.f : 270.f;
            if (iw) angle = Math::Lerp(angle, 0.f, 0.5f);
            else if (Input::KeyHold(InputKey::S)) angle = Math::Lerp(angle, 180.f, 0.5f);
            rottar = camscr->ry + angle + 180;
            tr->localPosition(tr->localPosition() + tr->forward() * moveSp * Time::delta());
            setclip(runClip);
        }
        else
            setclip(idleClip);
        
        static float rot0 = tr->localRotationEuler().y;
        rot0 = Math::LerpAngle(rot0, rottar, rotSp * Time::delta());
        tr->localRotationEuler(Vec3(0, rot0, 0));
    }
    void OnPaint() override {
        
    }
};

CE_END_NAMESPACE
