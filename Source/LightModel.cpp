#include "LightModel.h"
#include "EventManager.h"
#include "Renderer.h"

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
    float moveSpeed = 4.0f;
    glm::vec3 xDirection(1.0f, 0.0f, 0.0f);
    glm::vec3 yDirection(0.0f, 1.0f, 0.0f);
    glm::vec3 zDirection(0.0, 0.0f, 1.0f);

    // Update camera position
    vec3 delta = vec3(0.0f, 0.0f, 0.0f);
    if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_I) == GLFW_PRESS)
    {
        delta += zDirection * dt * moveSpeed;
    }
    if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_K) == GLFW_PRESS)
    {
        delta -= zDirection * dt * moveSpeed;
    }
    if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_J) == GLFW_PRESS)
    {
        delta += xDirection * dt * moveSpeed;
    }
    if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_L) == GLFW_PRESS)
    {
        delta -= xDirection * dt * moveSpeed;
    }
    if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_U) == GLFW_PRESS)
    {
        delta -= yDirection * dt * moveSpeed;
    }
    if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_O) == GLFW_PRESS)
    {
        delta += yDirection * dt * moveSpeed;
    }
    lightPosition += vec4(delta, 0);
    mPosition += delta;
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