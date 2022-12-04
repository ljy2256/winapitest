#pragma once
#include "Scene.h"
class Scene_Start :
    public Scene
{
public:
    virtual void Enter() override;
    virtual void Exit() override;
    virtual void Update() override;
public:
    Scene_Start();
    ~Scene_Start();
};

