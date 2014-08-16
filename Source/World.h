//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 8/7/14.
//
// Copyright (c) 2014 Concordia University. All rights reserved.
//

#pragma once

#include <vector>

class Camera;
class Model;
class LightModel;
class BSpline;

class World
{
public:
	World();
	~World();
	
	void Update(float dt);
	void Draw();

	void LoadScene(const char * scene_path);
    static Camera* GetCurrentCamera();
	static unsigned int GetCurrentCameraNumber(){return mCurrentCamera;}

    static std::vector<Model*>* GetModelsPtr();
    static std::vector<LightModel*>* GetLightModelsPtr();
    static std::vector<BSpline*>* GetBSplineModelsPtr();

private:
	static std::vector<Model*> mModel;
    static std::vector<LightModel*> mLightModels;
    static std::vector<BSpline*> mBSplineModels;

	static std::vector<Camera*> mCamera;
	static unsigned int mCurrentCamera;
};