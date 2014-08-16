#include <GLM/glm.hpp>
#include "RayCast.h"


RayCast::RayCast()
{
}

bool RayCast::LinePlaneIntersection(vec4 originPoint, vec4 directionVector, vec4 p1, vec4 p2, vec4 p3) {

	vec3 lineOnPlane1 = vec3(p2 - p1);
	vec3 lineOnPlane2 = vec3(p3 - p1);
	vec4 normal = normalize(vec4(glm::cross(lineOnPlane1, lineOnPlane2), 0.0f));

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

//bool RayCast::LinePlaneIntersection(vec4 originPoint, vec4 directionVector) {
//
//	vec3 lineOnPlane1 = vec3(p2 - p1);
//	vec3 lineOnPlane2 = vec3(p3 - p1);
//	vec4 normal = normalize(vec4(glm::cross(lineOnPlane1, lineOnPlane2), 1.0f));
//
//	float topPart = glm::dot(originPoint, normal);
//	float bottomPart = glm::dot(directionVector, normal);
//	float t = -(topPart / bottomPart);
//	std::cout << t << std::endl;
//
//	if (t > 0) {
//		return true;
//	}
//	else {
//		return false;
//	}
//}


RayCast::~RayCast()
{
}
