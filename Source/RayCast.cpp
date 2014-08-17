#include <GLM/glm.hpp>
#include "RayCast.h"


RayCast::RayCast()
{
}

bool RayCast::IsPlaneIntersecting(vec4 originPoint, vec4 directionVector, vec4 p1, vec4 p2, vec4 p3) {

	vec3 p1p2Vector = vec3(p2 - p1);
	vec3 p1p3Vector = vec3(p3 - p1);
	vec4 normal = normalize(vec4(glm::cross(p1p2Vector, p1p3Vector), 0.0f));

	// calculate plane
	float d = glm::dot(normal, p1);
	
	float numerator = glm::dot(originPoint, normal) + d;
	float denomerator = glm::dot(glm::normalize(directionVector), normal);
	float t = -(numerator / denomerator);
	std::cout << t << std::endl;
	
	if (t > 0) {
		return true;
	}
	else {
		return false;
	}
}

int RayCast::LinePlaneIntersection(vec4 originPoint, vec4 directionVector, vec3 p1, vec3 p2, vec3 p3) {

    vec3 p1p2Vector = p2 - p1;
    vec3 p1p3Vector = p3 - p1;
    vec4 normal = vec4(glm::cross(p1p2Vector, p1p3Vector), 0.0f);
    vec4 normalizedNormal = normalize(vec4(glm::cross(p1p2Vector, p1p3Vector), 0.0f));

    std::cout << "p1 {" << p1.x << " " << p1.y << " " << p1.z << "}" << std::endl;
    std::cout << "p2 {" << p2.x << " " << p2.y << " " << p2.z << "}" << std::endl;
    std::cout << "p3 {" << p3.x << " " << p3.y << " " << p3.z << "}" << std::endl;

    float originalTriangleArea = (glm::length(normal)) / 2.0f;
    std::cout << "originalTriangleArea {" << originalTriangleArea << "}" << std::endl;

    // calculate distance offset from origin
    //float d = glm::dot(normalizedNormal, vec4(p1, 1.0f));

    //Calculating t value in t = - (originPoint * normal + d)/ (directionVector * normal)
    float numerator = glm::dot(originPoint, normalizedNormal);
    float denomerator = glm::dot(glm::normalize(directionVector), normalizedNormal);
    float t = -(numerator / denomerator);
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
