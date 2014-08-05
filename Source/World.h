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

class World
{
public:
	World();
	~World();
	
	void Update(float dt);
	void Draw();

	void LoadScene(const char * scene_path);
    static Camera* GetCurrentCamera();

private:
	std::vector<Model*> mModel;
    std::vector<LightModel*> mLightModels;

	static std::vector<Camera*> mCamera;
	static unsigned int mCurrentCamera;
};