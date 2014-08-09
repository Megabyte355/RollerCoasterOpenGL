//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 8/7/14.
//
// Copyright (c) 2014 Concordia University. All rights reserved.
//

#pragma once

#include "Model.h"
#include <vector>
#include "CubeModel.h"

class VehicleModel : public Model
{
public:
	VehicleModel();
	virtual ~VehicleModel();

	virtual void Update(float dt);
	virtual void Draw();

protected:
	virtual bool ParseLine(const std::vector<ci_string> &token);

private:
	// @TODO 5 - You may want a container for all the parts of your vehicle
	CubeModel * mFrame;
	CubeModel * mBase;
	CubeModel * mCanon;
	CubeModel * mCanonBullet;
};
