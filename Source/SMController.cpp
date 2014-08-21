// Contributors:
//      Gary Chang

#include "SMController.h"

SMController::SMController(Model* model)
{
    this->model = model;
    Init();
}

SMController::~SMController()
{
    model = nullptr;
}

void SMController::Init()
{
}