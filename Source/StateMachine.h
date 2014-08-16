// Contributor:
//      Gary Chang

#pragma once

#include "Model.h"

class StateMachine
{
public:
    StateMachine(Model * m);
    virtual ~StateMachine();

    virtual void Init() = 0;
    virtual void Update(float dt) = 0;
    virtual void Draw() = 0;

    virtual void In() = 0;
    virtual void Out() = 0;
    virtual void Execute() = 0;

protected:
    Model* mModel;
};
