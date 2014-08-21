// Contributors:
//      Gary Chang

//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 8/7/14.
//
// Copyright (c) 2014 Concordia University. All rights reserved.
//

#pragma once

#include "Model.h"
#include "LightModel.h"
#include <vector>
#include "CubeModel.h"

class VehicleModel : public Model
{
public:
	VehicleModel();
	virtual ~VehicleModel();

	virtual void Update(float dt);
	virtual void Draw();

    virtual void SetLightSource(LightModel * lightSource);

protected:
	virtual bool ParseLine(const std::vector<ci_string> &token);

private:
	// @TODO 5 - You may want a container for all the parts of your vehicle
	std::vector<CubeModel*> container;
	std::vector<CubeModel*> rotatingXAxis;
	std::vector<CubeModel*> rotatingYAxis;

	float angularSpeedXAxis;
	float angularSpeedYAxis;
};
