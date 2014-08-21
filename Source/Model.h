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

#pragma once

#include "ParsingHelper.h"
#include "Renderer.h"
#include <vector>

#include <GLM/glm.hpp>

class LightModel;
class BSpline;
class BoundingBox;

class Model
{
public:
	// @TODO 4 - It could be a good idea to allow passing a parent model in the constructor
	Model();
    Model(Model * p);
    Model(Model * p, bool getScalingFromParent);
	virtual ~Model();

    virtual void Init();
	virtual void Update(float dt) = 0;
	virtual void Draw() = 0;
	void Load(ci_istringstream& iss);

	virtual glm::mat4 GetWorldMatrix() const;
    virtual glm::mat4 GetWorldMatrixWithoutScaling() const;
    virtual glm::mat4 GetViewMatrix() const;
    virtual glm::mat4 GetProjectionMatrix() const;
	virtual float     GetChildHorizontalAngle() { return 0; }
	virtual float     GetChildVerticalAngle() { return 0; }

	void SetPosition(glm::vec3 position);
	void SetScaling(glm::vec3 scaling);
	void SetRotation(glm::vec3 axis, float angleDegrees);
	void SetSecondRotation(glm::vec3 axis, float angleDegrees);
    virtual void SetLightSource(LightModel * lightModel);
	virtual void SetSplineSource(BSpline* splineSource);
    BSpline* GetSpline();
    bool LooksForward();

	glm::vec3 GetPosition() const		{ return mPosition; }
	glm::vec3 GetScaling() const		{ return mScaling; }
	glm::vec3 GetRotationAxis() const	{ return mRotationAxis; }
	glm::vec3 GetSecondRotationAxis() const	{ return mSecondRotationAxis; }
	float     GetRotationAngle() const	{ return mRotationAngleInDegrees; }
	float     GetSecondRotationAngle() const	{ return mSecondRotationAngleInDegrees; }
    LightModel* GetLightSource() { return mLightSource; }
	BSpline* GetBSpline() { return spline; }

	bool mGetScalingFromParent;
    // The vertex format could be different for different types of models
    struct Vertex
    {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec3 color;
    };

    virtual std::vector<Vertex> GetWorldVertices();
	BoundingBox* boundingBox;
	std::vector<Vertex> vertexBuffer;
	ci_string mName; // The model name is mainly for debugging
    
    glm::vec3 mForward;
    glm::vec3 mRight;
    glm::vec3 mUp;

protected:
	virtual bool ParseLine(const std::vector<ci_string> &token) = 0;
	ci_string texturePath;
	void DrawBoundingBox();


	glm::vec3 mPosition;
	glm::vec3 mScaling;
	glm::vec3 mRotationAxis;
	glm::vec3 mSecondRotationAxis;
	float     mRotationAngleInDegrees;
	float     mSecondRotationAngleInDegrees;
    bool      lookForward;

	// @TODO 4 - You may want to add a parent object for the hierarchical modeling
    Model * mParent;
    LightModel * mLightSource;


    // Shader coefficients
    float ka;
    float kd;
    float ks;
    float n;

	unsigned int mVertexArrayID;
	unsigned int mVertexBufferID;
	unsigned int uvbuffer;
	unsigned int m;
    BSpline* spline;

};