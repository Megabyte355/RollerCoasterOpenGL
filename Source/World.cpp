//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 8/7/14.
//
// Copyright (c) 2014 Concordia University. All rights reserved.
//

#include "World.h"
#include "Renderer.h"
#include "ParsingHelper.h"

#include "StaticCamera.h"
#include "FirstPersonCamera.h"

#include "CubeModel.h"
#include "VehicleModel.h"
#include "SphereModel.h"
#include "LightModel.h"
#include "BSpline.h"
#include "TriangleModel.h"

#include <GLFW/glfw3.h>
#include "EventManager.h"

using namespace std;
using namespace glm;

unsigned int World::mCurrentCamera;
std::vector<Camera*> World::mCamera;
std::vector<Model*> World::mModel;
std::vector<LightModel*> World::mLightModels;
std::vector<BSpline*> World::mBSplineModels;

World::World()
{
	// Setup Camera
	mCamera.push_back( new StaticCamera( vec3(3.0f, 4.0f, 5.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f) ) );
	mCamera.push_back( new FirstPersonCamera( vec3(0.5f, 0.5f, 5.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f) ) );
	mCurrentCamera = 0;

	// The geometry should be loaded from a scene file
}

World::~World()
{
	// Models
	for (vector<Model*>::iterator it = mModel.begin(); it < mModel.end(); ++it)
	{
		delete *it;
	}

	mModel.clear();

	// Camera
	for (vector<Camera*>::iterator it = mCamera.begin(); it < mCamera.end(); ++it)
	{
		delete *it;
	}
	mCamera.clear();

    // Lights
    for (vector<LightModel*>::iterator it = mLightModels.begin(); it < mLightModels.end(); ++it)
    {
        delete *it;
    }
    mLightModels.clear();
}
	
void World::Update(float dt)
{
	// User Inputs
	// 0 1 2 to change the Camera
	if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_1 ) == GLFW_PRESS)
	{
		mCurrentCamera = 0;
	}
	else if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_2 ) == GLFW_PRESS)
	{
		if (mCamera.size() > 1)
		{
			mCurrentCamera = 1;
		}
	}
	else if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_3 ) == GLFW_PRESS)
	{
		if (mCamera.size() > 2)
		{
			mCurrentCamera = 2;
		}
	}

	// Spacebar to change the shader
	if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_0 ) == GLFW_PRESS)
	{
        Renderer::SetShader(SHADER_PHONG);
	}
	else if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_9 ) == GLFW_PRESS)
	{
        Renderer::SetShader(SHADER_GOURAUD);
	}
    else if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_8 ) == GLFW_PRESS)
	{
		Renderer::SetShader(SHADER_SOLID_COLOR);
	}
    else if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_7 ) == GLFW_PRESS)
	{
		Renderer::SetShader(SHADER_BLUE);
	}

	// Update current Camera
	mCamera[mCurrentCamera]->Update(dt);

	// Update models
	for (vector<Model*>::iterator it = mModel.begin(); it < mModel.end(); ++it)
	{
		(*it)->Update(dt);
	}
    for (vector<LightModel*>::iterator it = mLightModels.begin(); it < mLightModels.end(); ++it)
	{
		(*it)->Update(dt);
	}
}

void World::Draw()
{
	Renderer::BeginFrame();
	
	// Set Shader... In a more sofisticated application, each model could use a different shader
	// In our case, all the models use a common shader
	glUseProgram(Renderer::GetShaderProgramID());

	// This looks for the V and P Uniform variable in the Vertex Program
    GLuint projectionMatrix = glGetUniformLocation(Renderer::GetShaderProgramID(), "ProjectonTransform");
    GLuint viewMatrix = glGetUniformLocation(Renderer::GetShaderProgramID(), "ViewTransform");

	// Draw models
	for (vector<Model*>::iterator it = mModel.begin(); it < mModel.end(); ++it)
	{
		// Send the view and projection constants to the shader
		mat4 V = mCamera[mCurrentCamera]->GetViewMatrix();
		glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, &V[0][0]);

        mat4 P = mCamera[mCurrentCamera]->GetProjectionMatrix();
		glUniformMatrix4fv(projectionMatrix, 1, GL_FALSE, &P[0][0]);

		// Draw model
		(*it)->Draw();
	}

	Renderer::EndFrame();
}

void World::LoadScene(const char * scene_path)
{
	// Using case-insensitive strings and streams for easier parsing
	ci_ifstream input;
	input.open(scene_path, ios::in);

	// Invalid file
	if(input.fail() )
	{	 
		fprintf(stderr, "Error loading file: %s\n", scene_path);
		getchar();
		exit(-1);
	}

	ci_string item;
	while( std::getline( input, item, '[' ) )   
	{
        ci_istringstream iss( item );

		ci_string result;
		if( std::getline( iss, result, ']') )
		{
			if( result == "cube" )
			{
				// Box attributes
				CubeModel* cube = new CubeModel();
				cube->Load(iss);
				mModel.push_back(cube);
			}
			else if( result == "vehicle" )
			{
				// Box attributes
				VehicleModel* vehicle = new VehicleModel();
				vehicle->Load(iss);
				mModel.push_back(vehicle);
			}
            else if( result == "sphere" )
            {
                SphereModel* sphere = new SphereModel();
                sphere->Load(iss);
                mModel.push_back(sphere);
            }
            else if( result == "light" )
            {
                LightModel* light = new LightModel();
                light->Load(iss);
                mLightModels.push_back(light);
            }
            else if( result == "bspline" )
            {
                BSpline* bSpline = new BSpline();
                bSpline->Load(iss);
                mBSplineModels.push_back(bSpline);
            }
			else if (result == "triangle")
			{
				TriangleModel* triangle = new TriangleModel();
				triangle->Load(iss);
				mModel.push_back(triangle);
			}
			else if ( result.empty() == false && result[0] == '#')
			{
				// this is a comment line
			}
			else
			{
				fprintf(stderr, "Error loading scene file... !");
				getchar();
				exit(-1);
			}
	    }
	}
	input.close();

    for (vector<Model*>::iterator it = mModel.begin(); it < mModel.end(); ++it)
	{
        // Temporary for single light source
		(*it)->SetLightSource(mLightModels.back());
	}
}

Camera* World::GetCurrentCamera()
{
    return mCamera[mCurrentCamera];
}

std::vector<Model*>* World::GetModelsPtr()
{
    return &mModel;
}

std::vector<LightModel*>* World::GetLightModelsPtr()
{
    return &mLightModels;
}

std::vector<BSpline*>* World::GetBSplineModelsPtr()
{
    return &mBSplineModels;
}