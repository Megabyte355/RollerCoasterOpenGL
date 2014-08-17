// Contributors:
//      Gary Chang

#pragma once

#include "Model.h"

class SMController
{
public:
    // @TODO 4 - It could be a good idea to allow passing a parent model in the constructor
    SMController(Model* model);
    virtual ~SMController();

    virtual void Update(float dt) = 0;
    virtual void In() = 0;
    virtual void Out() = 0;
    virtual void Execute() = 0;

protected:
    virtual void Init() = 0;

    Model* model;
};
