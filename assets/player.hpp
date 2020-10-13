#pragma once
#include "chokolait.hpp"
#include "camera.hpp"

CE_BEGIN_NAMESPACE

CE_SCRIPT_DEF(Ppl) {
public:
    CE_SERIALIZE float moveSp;
    CE_SERIALIZE float jumpingMoveSp;
    CE_SERIALIZE SceneObject camAxis;
    
    CE_SERIALIZE float rotSp;
    
    CE_SERIALIZE float jumpLen;
    CE_SERIALIZE float jumpHt;

    pTransform tr;
    Animator anim;
    
    Cam camscr;
    
    float _jumptime = -1;
    float _jumpy0;
    
    float rottar = 0.f;
    
    void OnStart() override {
        camscr = camAxis->children()[0]->GetComponent<Cam>();
        
        anim = object()->GetComponent<Animator>();
        tr = object()->transform();
        
        _jumpy0 = tr->localPosition().y;
    }
    void OnUpdate() override {
        bool iw = Input::KeyHold(InputKey::W);
        bool ia = Input::KeyHold(InputKey::A);
        bool is = Input::KeyHold(InputKey::S);
        bool id = Input::KeyHold(InputKey::D);
        if (iw || ia || is || id) {
            float angle = iw ? 0.f : 180.f;
            if (ia) angle = iw ? -90.f : 270.f;
            if (id) angle = 90.f;
            if (iw) angle = Math::Lerp(angle, 0.f, 0.5f);
            else if (Input::KeyHold(InputKey::S)) angle = Math::Lerp(angle, 180.f, 0.5f);
            rottar = camscr->ry + angle;
            tr->localPosition(tr->localPosition() + tr->forward() * ((_jumptime > 0) ? jumpingMoveSp : moveSp) * Time::delta());
            anim->SetBool("move", true);
            anim->SetFloat("movef", 1);
        }
        else {
            anim->SetBool("move", false);
            anim->SetFloat("movef", 0);
        }
        
        if (_jumptime > 0) {
            _jumptime += Time::delta();
            if (_jumptime > jumpLen) {
                anim->SetBool("jump", false);
                _jumptime = 0;
            }
            auto pos = tr->localPosition();
            const float jt = _jumptime / jumpLen;
            pos.y = jumpHt * std::pow(4 * (jt - jt*jt), 0.5f);
            tr->localPosition(pos);
        }
        else if (Input::KeyDown(InputKey::Space)) {
            anim->SetBool("jump", true);
            anim->PlayState("jump");
            _jumptime = 0.01f;
        }
        
        static float rot0 = tr->localRotationEuler().y;
        rot0 = Math::LerpAngle(rot0, rottar, rotSp * Time::delta());
        tr->localRotationEuler(Vec3(0, rot0, 0));
    }
    void OnPaint() override {
        
    }
};

CE_END_NAMESPACE
