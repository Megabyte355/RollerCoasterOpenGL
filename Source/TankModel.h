// Contributors:
//      Dong Li
//      Oleksandr Dymov

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

class TankModel : public Model
{
public:
	TankModel();
	virtual ~TankModel();

	virtual void Update(float dt);
	virtual void Draw();

	virtual void SetLightSource(LightModel * lightSource);
	virtual glm::vec3 GetCanonTipPoint();
	virtual glm::vec3 GetCanonDirectionVector();

	float GetChildHorizontalAngle() { return mChildHorizontalAngle; }
	float GetChildVerticalAngle() { return mChildVerticalAngle; }

protected:
	virtual bool ParseLine(const std::vector<ci_string> &token);

private:
	std::vector<CubeModel*> container;
	//Hold the rotation angle value in degree
	float mChildHorizontalAngle;
	float mChildVerticalAngle;
};
