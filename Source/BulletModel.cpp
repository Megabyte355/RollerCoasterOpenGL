//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 8/7/14.
//
// Copyright (c) 2014 Concordia University. All rights reserved.
//

#include "BulletModel.h"
#include "Renderer.h"

// Include GLEW - OpenGL Extension Wrangler
#include <GL/glew.h>

using namespace glm;

BulletModel::BulletModel(vec3 size)
{
    mParent = nullptr;
    mLightSource = nullptr;
    Init(size);
}

BulletModel::BulletModel(Model * parent, vec3 size)
{
    mParent = parent;
    mLightSource = nullptr;
    mGetScalingFromParent = true;
    Init(size);
}

BulletModel::BulletModel(Model * parent, bool getScalingFromParent, vec3 size)
{
    mParent = parent;
    mLightSource = nullptr;
    mGetScalingFromParent = getScalingFromParent;
    Init(size);
}

BulletModel::~BulletModel()
{
	// Free the GPU from the Vertex Buffer
	glDeleteBuffers(1, &mVertexBufferID);
	glDeleteVertexArrays(1, &mVertexArrayID);
}

void BulletModel::Init(vec3 size)
{
    lifetime = 5.0f;
    bulletSpeed = 2.0f;
}

void BulletModel::SetForwardVector(vec3 vec)
{
    mForward = vec;
}

bool BulletModel::IsAlive()
{
    return lifetime <= 0.0f;
}

void BulletModel::Update(float dt)
{
    lifetime -= dt;
    mPosition += mForward * bulletSpeed * dt;
}