//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 8/7/14.
//
// Copyright (c) 2014 Concordia University. All rights reserved.
//

#include "VehicleModel.h"
#include "CubeModel.h"


using namespace std;
using namespace glm;

VehicleModel::VehicleModel()
{
	// @TODO 5 - Layout your vehicle in a hierarchy
}

VehicleModel::~VehicleModel()
{
}

void VehicleModel::Update(float dt)
{	
	// @TODO 6 (Optional) - Here is where you can add some code if you want your vehicle to animate
}

void VehicleModel::Draw()
{
	// @TODO 5 - Draw Each part of your vehicle here
}

bool VehicleModel::ParseLine(const std::vector<ci_string> &token)
{
	if (token.empty())
	{
		return true;
	}
	else
	{
		return Model::ParseLine(token);
	}
}
