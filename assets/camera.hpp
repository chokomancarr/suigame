#pragma once
#include "chokolait.hpp"

CE_BEGIN_NAMESPACE

CE_SCRIPT_DEF(Cam) {
public:
    CE_SERIALIZE SceneObject ppl;
    CE_SERIALIZE float rotSp;
    CE_SERIALIZE float followSp;
    pTransform axis = nullptr;
    float ry = 0;

    void OnStart() override {
        axis = object()->parent()->transform();
    }
    void OnUpdate() override {
        if (Input::KeyHold(InputKey::RightArrow))
            ry -= rotSp * Time::delta();
        if (Input::KeyHold(InputKey::LeftArrow))
            ry += rotSp * Time::delta();
        axis->worldRotationEuler(Vec3(0, ry, 0));
    }
    void OnLateUpdate() override {
        axis->worldPosition(Math::Lerp(axis->worldPosition(), ppl->transform()->worldPosition(), followSp * Time::delta()));
    }
    void OnPaint() override {
        
    }
};

CE_END_NAMESPACE
