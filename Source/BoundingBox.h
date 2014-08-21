// Contributors:
//      Kevin Silva
//      Shahrad Rezaei

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/common.hpp>
#include "Model.h"
#include <vector>
#include "CubeModel.h"

class BoundingBox
{
public:
	BoundingBox(Model* parent);

	struct BoundingCube
	{
		std::vector<std::vector < glm::vec3 >> frontFace;
		std::vector<std::vector < glm::vec3 >> rightFace;
		std::vector<std::vector < glm::vec3 >> leftFace;
		std::vector<std::vector < glm::vec3 >> backFace;
		std::vector<std::vector < glm::vec3 >> topFace;
		std::vector<std::vector < glm::vec3 >> downFace;
	};
	
	bool HasObjectCollidedWithAnotherAABB(BoundingBox* OtherBox);
	BoundingCube CalculateBoundingBoxCoordinates();

private:
	glm::vec3 GetModelScalingFactor();

	struct Vertex
	{
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec3 color;
	};
	std::vector<Vertex> vertexBuffer;
	float scalingFactor;
	Model* model;
};