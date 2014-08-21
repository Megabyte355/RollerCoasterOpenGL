// Contributors:
//      Gary Chang
//  	Oleksandr Dymov

#include "LightModel.h"
#include "EventManager.h"
#include "Renderer.h"
#include "World.h"

#include <GLFW/glfw3.h>

using namespace glm;

LightModel::LightModel()
{
    Init();
}


LightModel::LightModel(Model * parent)
{
    mParent = parent;
    mGetScalingFromParent = true;
    Init();
}

LightModel::~LightModel()
{
}

void LightModel::Init()
{
    // Light Coefficients
    lightColor = vec3(1.0f, 1.0f, 1.0f);
    lightKc = 0.0f;
    lightKl = 0.0f;
    lightKq = 0.2f;
    lightPosition = vec4(0.0f, 0.0f, 0.0f, 1.0f); // If w = 1.0f, we have a point light
    //lightPosition = vec4(5.0f, 5.0f, -5.0f, 0.0f); // If w = 0.0f, we have a directional light
}

void LightModel::Update(float dt)
{
	// Distinction between the light from the sun
	if (mParent != nullptr) 
	{
		// Calculation of angle between plane and sun position by the dot product method
		sunAngle = acos(dot(vec3(lightPosition.x, lightPosition.y, lightPosition.z), vec3(0.0f, 1.0f, 0.0f)) 
			/ (float (length(vec3(lightPosition.x, lightPosition.y, lightPosition.z)) * length(vec3(0.0f, 1.0f, 0.0f))))); 

		// Make angle in to proportion
		sunAngle = sunAngle/1.57 - 0.07;
		
		// In case it is a sun, put the light between it and the map
		lightPosition = vec4(this->mParent->GetPosition()*0.71f, 1);

		// To make the sunrise/sunset more realistic by placing light higher at these moments
		if ((lightPosition.y > 59.5 || lightPosition.x < -59.5) && lightPosition.y < 1)
		{
			// Varying light position according to angle
			lightPosition.y = 2; 
		}

		// Varying Light color through the day
		lightColor.x = 0.965f/sunAngle;
		lightColor.y = 0.545f/sunAngle;
		lightColor.z = 0.122f/sunAngle;
	}
	else
	{
		lightPosition = vec4(mPosition, lightPosition.w);
	}

	// Debug Purposes
	//std::cout << "Sun angle: " << lightPosition.x << std::endl;
	//std::cout << "light position x: " << mPosition.x << std::endl;
	//std::cout << "light position y : " << mPosition.y << std::endl;
	//std::cout << "light position z: " << mPosition.z << std::endl << std::endl;
}

void LightModel::Draw()
{
}

bool LightModel::ParseLine(const std::vector<ci_string> &token)
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

void LightModel::SetShaderConstants(float ka, float kd, float ks, float n)
{
    // Get a handle for Light Attributes uniform
    GLuint LightPositionID = glGetUniformLocation(Renderer::GetShaderProgramID(), "WorldLightPosition");
    GLuint LightColorID = glGetUniformLocation(Renderer::GetShaderProgramID(), "lightColor");
    GLuint LightAttenuationID = glGetUniformLocation(Renderer::GetShaderProgramID(), "lightAttenuation");

    // Get a handle for Material Attributes uniform
    GLuint MaterialID = glGetUniformLocation(Renderer::GetShaderProgramID(), "materialCoefficients");

	glUniform4f(MaterialID, ka, kd, ks, n);
	glUniform4f(LightPositionID, lightPosition.x, lightPosition.y, lightPosition.z, lightPosition.w);
	glUniform3f(LightColorID, lightColor.r, lightColor.g, lightColor.b);
	glUniform3f(LightAttenuationID, lightKc, lightKl, lightKq);
}
