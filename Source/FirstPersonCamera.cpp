// Contributors:
//      Razvan Alin Cijov
//      Gary Chang
//      Dong Li
//      Oleksandr Dymov

#include "FirstPersonCamera.h"
#include "RayCast.h"
#include "ParticleEmitter.h"
#include "BulletModel.h"
#include "World.h"
#include "TankModel.h"
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include "EventManager.h"

using namespace glm;


FirstPersonCamera::FirstPersonCamera(glm::vec3 offset, glm::vec3 lookAtPoint, glm::vec3 upVector) 
	: Camera()
{
	mOffset = offset;
	mLookAtPoint = lookAtPoint;
	mUpVector = upVector;
}

FirstPersonCamera::~FirstPersonCamera()
{
}

void FirstPersonCamera::Update(float dt)
{
	EventManager::DisableMouseCursor();

	float pi = radians(180.0f);
	//Get postion and turned angle from the attached object(tank)
	glm::vec3 targetPosition = mTarget -> GetPosition();
	float tankHorizontalAngle = mTarget -> GetRotationAngle();
	float tankHAngleRadians = radians(tankHorizontalAngle);

	//Get turned angle from the canon
	float canonHorizontalAngle = mTarget -> GetChildHorizontalAngle();
	float canonVerticalAngle = mTarget -> GetChildVerticalAngle();
	float canonHAngleRadian = radians(canonHorizontalAngle);
	float canonVAngleRadian = radians(-canonVerticalAngle);

	//update postion and lookat for the camera
	mPosition = targetPosition + vec3(sinf(tankHAngleRadians + canonHAngleRadian) * cosf(atan2(mOffset.y, mOffset.z) + canonVAngleRadian) * (sqrtf(powf(mOffset.y, 2) + powf(mOffset.z, 2))), sinf(atan2(mOffset.y, mOffset.z) + canonVAngleRadian) * (sqrtf(powf(mOffset.y, 2) + powf(mOffset.z, 2))), cosf(tankHAngleRadians + canonHAngleRadian) * cosf(atan2(mOffset.y, mOffset.z) + canonVAngleRadian) * (sqrtf(powf(mOffset.y, 2) + powf(mOffset.z, 2))));
	mLookAtPoint = mPosition + vec3(sinf(tankHAngleRadians + canonHAngleRadian) * cosf(canonVAngleRadian), sinf(canonVAngleRadian), cosf(tankHAngleRadians + canonHAngleRadian)*cosf(canonVAngleRadian)); 

    if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_SPACE) == GLFW_PRESS && spaceReleased)
    {
        TankModel* tank = dynamic_cast<TankModel*>(mTarget);
        if (tank != nullptr)
        {
            RayCast::CollisionResult collision = RayCast::IntersectBoundingBoxes(vec4(tank->GetCanonTipPoint(), 1.0f), vec4(tank->GetCanonDirectionVector(), 1.0f));

            std::string modelName = "empty";
            if (collision.model != nullptr)
            {
                modelName = collision.model->mName.c_str();
            }
            std::cout << "Collided Model: " << modelName << std::endl;
            std::cout << "Collision point x: " << collision.collisionPointWorld.x << std::endl;
            std::cout << "Collision point y: " << collision.collisionPointWorld.y << std::endl;
            std::cout << "Collision point z: " << collision.collisionPointWorld.z << std::endl << std::endl;

            if (collision.collision)
            {
                glm::vec3 colorA = glm::vec3(1.0f, 0.0f, 0.0f);
                glm::vec3 colorB = glm::vec3(1.0f, 1.0f, 0.0f);

                ParticleEmitter* emitter = new ParticleEmitter(collision.collisionPointWorld, collision.normal, colorA, colorB);
                World::GetModelsPtr()->push_back(emitter);
                emitter->SetLightSource(World::GetLightModelsPtr()->back());
                emitter->GenerateParticles();
            }
        }
        glm::vec3 colorC = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 colorD = glm::vec3(1.0f, 1.0f, 1.0f);

        ParticleEmitter* emitter2 = new ParticleEmitter(vec4(tank->GetCanonTipPoint(), 1.0f), vec4(0,0,0,0), colorC, colorD);
        World::GetModelsPtr()->push_back(emitter2);
        emitter2->SetLightSource(World::GetLightModelsPtr()->back());
        emitter2->GenerateParticles();
        spaceReleased = false;
    }

    if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_SPACE) == GLFW_RELEASE)
    {
        spaceReleased = true;
    }

    // Implementation of the bullet shooting with a control for single bullet per key press
    if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_B) == GLFW_PRESS && buttonReleased)
	{
        TankModel* tank = dynamic_cast<TankModel*>(mTarget);
       	// Checks if it is a Tank first
        if (tank != nullptr)
        {
       	    // Generates a bullet and sends in the canon direction
            BulletModel* bullet = new BulletModel();
            bullet->SetLightSource(World::GetLightModelsPtr()->back());
            bullet->SetCoordinates(tank->GetCanonTipPoint(), tank->GetCanonDirectionVector());
            World::GetModelsPtr()->push_back(bullet);
            buttonReleased = false;
        }
	}
    if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_B) == GLFW_RELEASE)
    {
        buttonReleased = true;
    }
}

glm::mat4 FirstPersonCamera::GetViewMatrix() const
{
	return glm::lookAt(		mPosition,		// Camera position
							mLookAtPoint,	// Look towards this point
							mUpVector		// Up vector
						);
}

void FirstPersonCamera::setTarget(Model* target){
	mTarget = target;
}

void FirstPersonCamera::StartCameraShake(float dt)
{
	timeElapsed += dt;
	amplitude += adjustAmplitudePerSecond * dt;
	mPosition.y += +sin(timeElapsed);
}

void FirstPersonCamera::SetCameraShake(float amplitude, float adjustAmplitudePerSecond)
{
	this->amplitude = amplitude;
	this->adjustAmplitudePerSecond = adjustAmplitudePerSecond;
}
