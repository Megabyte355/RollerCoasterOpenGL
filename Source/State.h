// Contributors:
//      Gary Chang

#pragma once

#include "Model.h"

class State
{
public:
    State();
    virtual ~State();

    virtual void In() = 0;
    virtual void Out() = 0;
    virtual void Execute(float dt) = 0;
    virtual bool IsExpired();

    std::string GetName() { return name; }
    std::string GetNextStateName() { return nextStateName; }

protected:
    virtual void Init() = 0;
    float duration;
    std::string name;
    std::string nextStateName;
};
