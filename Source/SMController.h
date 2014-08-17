// Contributors:
//      Gary Chang

#pragma once

#include "Model.h"

class SMController
{
public:
    SMController(Model* model);
    virtual ~SMController();

    virtual void Update(float dt) = 0;
    virtual void Init() = 0;

protected:
    Model* model;
};
