//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 8/7/14.
//
// Copyright (c) 2014 Concordia University. All rights reserved.
//

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