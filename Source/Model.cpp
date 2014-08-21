// Contributors:
//      Razvan Alin Cijov
//      Gary Chang
//      Kevin Silva
//      Shahrad Rezaei
//      Dong Li
//      Oleksandr Dymov

//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 8/7/14.
//
// Copyright (c) 2014 Concordia University. All rights reserved.
//

#include "Model.h"
#include "World.h"
#include "StaticCamera.h"
#include "FirstPersonCamera.h"
#include "FreeLookCamera.h"
#include "BSpline.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/common.hpp>
#include "BoundingBox.h"

#include <iostream>

using namespace std;

Model::Model() : mName("UNNAMED"), mPosition(0.0f, 0.0f, 0.0f), mScaling(1.0f, 1.0f, 1.0f), mRotationAxis(0.0f, 1.0f, 0.0f), mRotationAngleInDegrees(0.0f), mSecondRotationAxis(1.0f, 0.0f, 0.0f), mSecondRotationAngleInDegrees(0.0f)
{
    mParent = nullptr;
    mGetScalingFromParent = true;
    spline = nullptr;
	boundingBox = new BoundingBox(this);
    Init();
}

Model::Model(Model * p) : mName("UNNAMED"), mPosition(0.0f, 0.0f, 0.0f), mScaling(1.0f, 1.0f, 1.0f), mRotationAxis(0.0f, 1.0f, 0.0f), mRotationAngleInDegrees(0.0f)
{
    mParent = p;
    mGetScalingFromParent = true;
    spline = nullptr;
	boundingBox = new BoundingBox(this);
    Init();
}

Model::Model(Model * p, bool getScalingFromParent) : mName("UNNAMED"), mPosition(0.0f, 0.0f, 0.0f), mScaling(1.0f, 1.0f, 1.0f), mRotationAxis(0.0f, 1.0f, 0.0f), mRotationAngleInDegrees(0.0f)
{
    mParent = p;
    mGetScalingFromParent = getScalingFromParent;
    spline = nullptr;
	boundingBox = new BoundingBox(this);
    Init();
}

Model::~Model()
{
}

void Model::Init()
{
    mForward = glm::vec3(0.0f, 0.0f, 1.0f);
    mUp = glm::vec3(0.0f, 1.0f, 0.0f);
    mRight = glm::cross(mForward, mUp);
    lookForward = true;
}

void Model::Update(float dt)
{
    if(spline != nullptr)
    {
        this->mPosition = spline->GetPosition() + spline->GetNextPoint();

        if (lookForward)
        {
            glm::vec3 velocity = glm::vec3(spline->GetVelocityUnitVector());
            mRotationAxis = glm::cross(mForward, velocity);
            mRotationAngleInDegrees = degrees(glm::acos(glm::dot(mForward, velocity) / (length(mForward) * length(velocity))));
        }
        spline->Update(dt);
    }
}

void Model::Draw()
{
}

void Model::Load(ci_istringstream& iss)
{
	ci_string line;

	// Parse model line by line
	while(std::getline(iss, line))
	{
		// Splitting line into tokens
		ci_istringstream strstr(line);
		istream_iterator<ci_string, char, ci_char_traits> it(strstr);
		istream_iterator<ci_string, char, ci_char_traits> end;
		vector<ci_string> token(it, end);

		if (ParseLine(token) == false)
		{
			fprintf(stderr, "Error loading scene file... token:  %s!", token[0]);
			getchar();
			exit(-1);
		}
	}
}

bool Model::ParseLine(const std::vector<ci_string> &token)
{
	if (token.empty() == false)
	{
		if (token[0].empty() == false && token[0][0] == '#')
		{
			return true;
		}
		else if (token[0] == "name")
		{
			assert(token.size() > 2);
			assert(token[1] == "=");

			mName = token[2];	
		}
		else if (token[0] == "position")
		{
			assert(token.size() > 4);
			assert(token[1] == "=");

			mPosition.x = static_cast<float>(atof(token[2].c_str()));
			mPosition.y = static_cast<float>(atof(token[3].c_str()));
			mPosition.z = static_cast<float>(atof(token[4].c_str()));
		}
		else if (token[0] == "rotation")
		{
			assert(token.size() > 4);
			assert(token[1] == "=");

			mRotationAxis.x = static_cast<float>(atof(token[2].c_str()));
			mRotationAxis.y = static_cast<float>(atof(token[3].c_str()));
			mRotationAxis.z = static_cast<float>(atof(token[4].c_str()));
			mRotationAngleInDegrees = static_cast<float>(atof(token[5].c_str()));

			glm::normalize(mRotationAxis);
		}
		else if (token[0] == "scaling")
		{
			assert(token.size() > 4);
			assert(token[1] == "=");

			mScaling.x = static_cast<float>(atof(token[2].c_str()));
			mScaling.y = static_cast<float>(atof(token[3].c_str()));
			mScaling.z = static_cast<float>(atof(token[4].c_str()));
		}
        else if (token[0] == "spline")
        {
            assert(token.size() > 2);
			assert(token[1] == "=");

            vector<BSpline*>* splineModels = World::GetBSplineModelsPtr();

            for(vector<BSpline*>::iterator it = splineModels->begin(); it < splineModels->end(); ++it)
            {
                if((*it)->mName == token[2])
                {
                    this->spline = dynamic_cast<BSpline*>(*it);
                    break;
                }
            }
            splineModels = nullptr;
        }
        else if (token[0] == "splinepoint")
        {
            assert(token.size() > 2);
			assert(token[1] == "=");

            BSpline* s = dynamic_cast<BSpline*>(this);
            if(this != nullptr)
            {
			    float x = static_cast<float>(atof(token[2].c_str()));
			    float y = static_cast<float>(atof(token[3].c_str()));
			    float z = static_cast<float>(atof(token[4].c_str()));
                float w = static_cast<float>(atof(token[5].c_str()));
                s->AddPoint(glm::vec4(x, y, z, w));
            }
        }
        else if (token[0] == "splinespeed")
        {
            assert(token.size() > 2);
			assert(token[1] == "=");

            BSpline* s = dynamic_cast<BSpline*>(this);
            if(this != nullptr)
            {
                float speed = static_cast<float>(atof(token[2].c_str()));
                s->SetSpeed(speed);
            }
        }
		else if (token[0] == "splineclosedloop")
		{
			assert(token.size() > 2);
			assert(token[1] == "=");

			BSpline* s = dynamic_cast<BSpline*>(this);
			if (this != nullptr)
			{
				bool loop = static_cast<bool>(atof(token[2].c_str()));
				s->SetClosedLoop(loop);
			}
		}
		else
		{
			return false;
		}
	}

	return true;
}

glm::mat4 Model::GetWorldMatrix() const
{
	// @TODO 2, you must build the world matrix from the position, scaling and rotation informations
    glm::mat4 identity = glm::mat4(1.0f);

    glm::mat4 position = glm::translate(identity, mPosition);
    glm::mat4 scale = glm::scale(identity, mScaling);
    glm::mat4 rotation = glm::rotate(identity, mRotationAngleInDegrees, mRotationAxis) * glm::rotate(identity, mSecondRotationAngleInDegrees, mSecondRotationAxis);

    glm::mat4 worldMatrix = position * rotation * scale;

	// @TODO 4 - Maybe you should use the parent world transform when you do hierarchical modeling
    if(mParent != nullptr)
    {
        if(mGetScalingFromParent)
        {
            return mParent->GetWorldMatrix() * worldMatrix;
        }
        else
        {
            return mParent->GetWorldMatrixWithoutScaling() * worldMatrix;
        }
    }
    else
    {
        return worldMatrix;
    }
}

glm::mat4 Model::GetWorldMatrixWithoutScaling() const
{
    glm::mat4 identity = glm::mat4(1.0f);
    glm::mat4 position = glm::translate(identity, mPosition);
    glm::mat4 rotation = glm::rotate(identity, mRotationAngleInDegrees, mRotationAxis);

    return position * rotation;
}

glm::mat4 Model::GetViewMatrix() const
{
    return World::GetCurrentCamera()->GetViewMatrix();
}

glm::mat4 Model::GetProjectionMatrix() const
{
    return World::GetCurrentCamera()->GetProjectionMatrix();
}

void Model::SetPosition(glm::vec3 position)
{
	mPosition = position;
}

void Model::SetScaling(glm::vec3 scaling)
{
	mScaling = scaling;
}

void Model::SetRotation(glm::vec3 axis, float angleDegrees)
{
	mRotationAxis = axis;
	mRotationAngleInDegrees = angleDegrees;
}

void Model::SetSecondRotation(glm::vec3 axis, float angleDegrees)
{
	mSecondRotationAxis = axis;
	mSecondRotationAngleInDegrees = angleDegrees;
}

void Model::SetLightSource(LightModel * lightSource)
{
    mLightSource = lightSource;
}

BSpline* Model::GetSpline()
{
    return spline;
}

bool Model::LooksForward()
{
    return lookForward;
}

std::vector<Model::Vertex> Model::GetWorldVertices() {
    std::vector<Vertex> vec;
    return vec;
}

void Model::SetSplineSource(BSpline* splineSource)
{
	spline = splineSource;
}

void Model::DrawBoundingBox()
{

}