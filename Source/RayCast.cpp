#include <GLM/glm.hpp>
#include "RayCast.h"


RayCast::RayCast()
{
}

int RayCast::IsPlaneIntersecting(vec4 originPoint, vec4 directionVector, vec3 p1, vec3 p2, vec3 p3) {

    std::cout << "p1 {" << p1.x << " " << p1.y << " " << p1.z << "}" << std::endl;
    std::cout << "p2 {" << p2.x << " " << p2.y << " " << p2.z << "}" << std::endl;
    std::cout << "p3 {" << p3.x << " " << p3.y << " " << p3.z << "}" << std::endl;

    vec4 w = originPoint - vec4(p1, 1.0f);

    vec3 p1p2Vector = p2 - p1;
    vec3 p1p3Vector = p3 - p1;
    vec4 normal = vec4(glm::cross(p1p2Vector, p1p3Vector), 0.0f);
    std::cout << "normal {" << normal.x << " " << normal.y << " " << normal.z << "}" << std::endl;
    vec4 normalizedNormal = normalize(normal);
    std::cout << "normalizedNormal {" << normalizedNormal.x << " " << normalizedNormal.y << " " << normalizedNormal.z << "}" << std::endl;

    float numerator = -glm::dot(normalizedNormal, glm::normalize(w));
    float denominator = glm::dot(normalizedNormal, directionVector);    
    
    // Line is parallel to plane
    if (fabs(denominator) < 0.0001f ) {           
        return false;
    }
    //Continue to compute intersecting point
    float t = numerator / denominator;
    std::cout << "t {" << t << "}" << std::endl;
    
    // no intersection
    if (t < 0 || t > 1) {
        return 0;
    }
    
    vec4 intersectionPoint = originPoint + t * directionVector;
    std::cout << "intersectionPoint {" << intersectionPoint.x << " " << intersectionPoint.y << " " << intersectionPoint.z << "}" << std::endl;
    return 1;
}

int RayCast::LinePlaneIntersection(vec4 originPoint, vec4 directionVector, vec3 p1, vec3 p2, vec3 p3)
{

    vec3 p1p2Vector = p2 - p1;
    vec3 p1p3Vector = p3 - p1;
    vec4 normal = vec4(glm::cross(p1p2Vector, p1p3Vector), 0.0f);
    vec4 normalizedNormal = normalize(normal);

    std::cout << "p1 {" << p1.x << " " << p1.y << " " << p1.z << "}" << std::endl;
    std::cout << "p2 {" << p2.x << " " << p2.y << " " << p2.z << "}" << std::endl;
    std::cout << "p3 {" << p3.x << " " << p3.y << " " << p3.z << "}" << std::endl;

    float originalTriangleArea = (glm::length(normal)) / 2.0f;
    std::cout << "originalTriangleArea {" << originalTriangleArea << "}" << std::endl;

    // calculate distance offset from origin
    float d = - glm::dot(normalizedNormal, vec4(p1, 1.0f));

    //Calculating t value in t = - (originPoint * normal + d)/ (directionVector * normal)
    float numerator = glm::dot(originPoint, normalizedNormal) + d;
    float denomerator = glm::dot(glm::normalize(directionVector), normalizedNormal);
    float t = -(numerator)  / denomerator;
    std::cout << "t {" << t << "}" << std::endl;

    //Finding resulting point on plane: P = originPoint + tv
    vec4 intersectionPoint = originPoint + t * directionVector;
    std::cout << "intersectionPoint {" << intersectionPoint.x << " " << intersectionPoint.y << " " << intersectionPoint.z << "}" << std::endl;

    //Check if point is bound within 3 points
    vec3 intersectionPointp1Vector = p1 - vec3(intersectionPoint);
    std::cout << "intersectionPointp1Vector {" << intersectionPointp1Vector.x << " " << intersectionPointp1Vector.y << " " << intersectionPointp1Vector.z << "}" << std::endl;
    vec3 intersectionPointp2Vector = p2 - vec3(intersectionPoint);
    std::cout << "intersectionPointp2Vector {" << intersectionPointp2Vector.x << " " << intersectionPointp2Vector.y << " " << intersectionPointp2Vector.z << "}" << std::endl;

    float areaTriangleA = (glm::length(vec3(glm::cross(p1 - vec3(intersectionPoint), p2 - vec3(intersectionPoint)))))/2.0f;
    float areaTriangleB = (glm::length(vec3(glm::cross(p2 - vec3(intersectionPoint), p3 - vec3(intersectionPoint))))) / 2.0f;
    float areaTriangleC = (glm::length(vec3(glm::cross(p1 - vec3(intersectionPoint), p3 - vec3(intersectionPoint))))) / 2.0f;

    std::cout << "areaTriangleA {" << areaTriangleA << "}" << std::endl;
    std::cout << "areaTriangleB {" << areaTriangleB << "}" << std::endl;
    std::cout << "areaTriangleC {" << areaTriangleC << "}" << std::endl;

    float totalArea = areaTriangleA + areaTriangleB + areaTriangleC;
    std::cout << "totalArea {" << totalArea << "}" << std::endl;

    return t;
}

RayCast::~RayCast()
{
}