// Utility class used to perform Ray Casting and AABB collisions
// Contributors:
//      Kevin Silva
//      Gary Chang

#include <GLM/glm.hpp>
#include "RayCast.h"
#include "World.h"
#include "BoundingBox.h"

RayCast::RayCast()
{
}

RayCast::CollisionResult RayCast::IntersectBoundingBoxes(vec4 originPoint, vec4 directionVector)
{
    std::vector<Model *> models = *World::GetModelsPtr();
    std::vector<CollisionResult> collisionResults;

    for (int i = 0; i < models.size(); i++)
    {
        Model* model = models.at(i);
        BoundingBox::BoundingCube boundingCube = model->boundingBox->CalculateBoundingBoxCoordinates();
        CollisionResult currentResult;

        if (boundingCube.frontFace.size() == 0)
        {
            continue;
        }

        //std::cout << "=================================" << std::endl;
        //std::cout << model->mName.c_str() << std::endl;
        //std::cout << "=================================" << std::endl;

        //std::cout << "Back face" << std::endl;
        vec3 p1 = boundingCube.backFace[0][0];
        vec3 p2 = boundingCube.backFace[0][1];
        vec3 p3 = boundingCube.backFace[0][2];
        currentResult = RayCast::Intersect3DTriangle(originPoint, directionVector, p1, p2, p3, model);
        if (currentResult.collision)
        {
            collisionResults.push_back(currentResult);
        }

        p1 = boundingCube.backFace[1][0];
        p2 = boundingCube.backFace[1][1];
        p3 = boundingCube.backFace[1][2];
        currentResult = RayCast::Intersect3DTriangle(originPoint, directionVector, p1, p2, p3, model);
        if (currentResult.collision)
        {
            collisionResults.push_back(currentResult);
        }

        //std::cout << "Front face" << std::endl;
        p1 = boundingCube.frontFace[0][0];
        p2 = boundingCube.frontFace[0][1];
        p3 = boundingCube.frontFace[0][2];
        currentResult = RayCast::Intersect3DTriangle(originPoint, directionVector, p1, p2, p3, model);
        if (currentResult.collision)
        {
            collisionResults.push_back(currentResult);
        }

        p1 = boundingCube.frontFace[1][0];
        p2 = boundingCube.frontFace[1][1];
        p3 = boundingCube.frontFace[1][2];
        currentResult = RayCast::Intersect3DTriangle(originPoint, directionVector, p1, p2, p3, model);
        if (currentResult.collision)
        {
            collisionResults.push_back(currentResult);
        }

        //std::cout << "Left face" << std::endl;
        p1 = boundingCube.leftFace[0][0];
        p2 = boundingCube.leftFace[0][1];
        p3 = boundingCube.leftFace[0][2];
        currentResult = RayCast::Intersect3DTriangle(originPoint, directionVector, p1, p2, p3, model);
        if (currentResult.collision)
        {
            collisionResults.push_back(currentResult);
        }

        p1 = boundingCube.leftFace[1][0];
        p2 = boundingCube.leftFace[1][1];
        p3 = boundingCube.leftFace[1][2];
        currentResult = RayCast::Intersect3DTriangle(originPoint, directionVector, p1, p2, p3, model);
        if (currentResult.collision)
        {
            collisionResults.push_back(currentResult);
        }

        //std::cout << "Right face" << std::endl;
        p1 = boundingCube.rightFace[0][0];
        p2 = boundingCube.rightFace[0][1];
        p3 = boundingCube.rightFace[0][2];
        currentResult = RayCast::Intersect3DTriangle(originPoint, directionVector, p1, p2, p3, model);
        if (currentResult.collision)
        {
            collisionResults.push_back(currentResult);
        }

        p1 = boundingCube.rightFace[1][0];
        p2 = boundingCube.rightFace[1][1];
        p3 = boundingCube.rightFace[1][2];
        currentResult = RayCast::Intersect3DTriangle(originPoint, directionVector, p1, p2, p3, model);
        if (currentResult.collision)
        {
            collisionResults.push_back(currentResult);
        }

        //std::cout << "Top face" << std::endl;
        p1 = boundingCube.topFace[0][0];
        p2 = boundingCube.topFace[0][1];
        p3 = boundingCube.topFace[0][2];
        currentResult = RayCast::Intersect3DTriangle(originPoint, directionVector, p1, p2, p3, model);
        if (currentResult.collision)
        {
            collisionResults.push_back(currentResult);
        }

        p1 = boundingCube.topFace[1][0];
        p2 = boundingCube.topFace[1][1];
        p3 = boundingCube.topFace[1][2];
        currentResult = RayCast::Intersect3DTriangle(originPoint, directionVector, p1, p2, p3, model);
        if (currentResult.collision)
        {
            collisionResults.push_back(currentResult);
        }

        //std::cout << "Down face" << std::endl;
        p1 = boundingCube.downFace[0][0];
        p2 = boundingCube.downFace[0][1];
        p3 = boundingCube.downFace[0][2];
        currentResult = RayCast::Intersect3DTriangle(originPoint, directionVector, p1, p2, p3, model);
        if (currentResult.collision)
        {
            collisionResults.push_back(currentResult);
        }

        p1 = boundingCube.downFace[1][0];
        p2 = boundingCube.downFace[1][1];
        p3 = boundingCube.downFace[1][2];
        currentResult = RayCast::Intersect3DTriangle(originPoint, directionVector, p1, p2, p3, model);
        if (currentResult.collision)
        {
            collisionResults.push_back(currentResult);
        }
    }

    if (collisionResults.size() > 0)
    {
        CollisionResult closestCollision = collisionResults.back();
        float minDistance = length(closestCollision.collisionPointWorld - originPoint);

        for each(CollisionResult c in collisionResults)
        {
            float currentDistance = length(c.collisionPointWorld - originPoint);
            if (currentDistance < minDistance)
            {
                closestCollision = c;
                minDistance = currentDistance;
            }
        }
        return closestCollision;
    }

    // No collision
    return
    {
        glm::vec4(0.0f, 0.0f, 0.0f, 0.0f),
        nullptr,
        glm::vec4(0.0f, 0.0f, 0.0f, 0.0f),
        false
    };
}

// intersect3D_SegmentPlane(): intersect a segment and a plane
//    Input:  originPoint = a point in model, directionVector = vector pointing at triangle, p1/p2/p3 = points that create 3D triangle
//    Return: 0 = disjoint (no intersection)
//            1 = intersection in the unique point intersectionPoint
RayCast::CollisionResult RayCast::Intersect3DTriangle(vec4 originPoint, vec4 directionVector, vec3 p1, vec3 p2, vec3 p3, Model* model) {

    CollisionResult cResult =
    {
        glm::vec4(0.0f, 0.0f, 0.0f, 0.0f),
        nullptr,
        glm::vec4(0.0f, 0.0f, 0.0f, 0.0f),
        false
    };

    vec4 w = originPoint - vec4(p1, 1.0f);

    vec3 p1p2Vector = p2 - p1;
    vec3 p1p3Vector = p3 - p1;
    vec4 normal = vec4(glm::cross(p1p2Vector, p1p3Vector), 0.0f);

    vec4 normalizedNormal = normalize(normal);

    // Calculate dot product is 90 < theta < 270  --> greater than 0
    if (glm::dot(normalizedNormal, glm::normalize(directionVector)) > 0.0f) {
        //std::cout << "NOT FACING US!!!" << std::endl;
        return cResult;
    }

    float numerator = -glm::dot(normalizedNormal, w);
    float denominator = glm::dot(normalizedNormal, directionVector);

    // Line is parallel to plane
    if (fabs(denominator) < 0.0001f) {
        return cResult;
    }
    //Continue to compute intersecting point
    float t = numerator / denominator;

    // no intersection
    if (t < 0) {
        return cResult;
    }

    //Finding resulting point on plane: P = originPoint + tv
    vec4 intersectionPoint = originPoint + t * directionVector;

    //Check if point is bound within 3 points
    vec3 intersectionPointp1Vector = p1 - vec3(intersectionPoint);
    vec3 intersectionPointp2Vector = p2 - vec3(intersectionPoint);

    float areaTriangleA = (glm::length(vec3(glm::cross(p1 - vec3(intersectionPoint), p2 - vec3(intersectionPoint))))) / 2.0f;
    float areaTriangleB = (glm::length(vec3(glm::cross(p2 - vec3(intersectionPoint), p3 - vec3(intersectionPoint))))) / 2.0f;
    float areaTriangleC = (glm::length(vec3(glm::cross(p1 - vec3(intersectionPoint), p3 - vec3(intersectionPoint))))) / 2.0f;
    float originalTriangleArea = (glm::length(normal)) / 2.0f;


    float totalArea = areaTriangleA + areaTriangleB + areaTriangleC;

    if (fabs(totalArea - originalTriangleArea) < 0.001f) {
        //std::cout << "SUPERU COLLISIONURU" << std::endl << std::endl;
        return
        {
            intersectionPoint,
            model,
            normalizedNormal,
            true
        };
    }

    //std::cout << "NOT COLLIDING!!!" << std::endl;
    return cResult;
}

RayCast::~RayCast()
{
}
