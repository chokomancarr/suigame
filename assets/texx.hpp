#pragma once
#include "chokolait.hpp"

CE_BEGIN_NAMESPACE

CE_SCRIPT_DEF(Texx) {
public:
    CE_SERIALIZE Texture tx;

    void OnStart() override {
        Debug::Message("Texx", "Hello, world!");
    }
    void OnUpdate() override {
        ChokoLait::scene->objects()[0]->transform()->localRotationEuler(Vec3(0, 45 * Time::time(), 0));
    }
    void OnPaint() override {
        UI::Texture(Rect(10, 10, 64, 64), tx);
    }
};

CE_END_NAMESPACE
