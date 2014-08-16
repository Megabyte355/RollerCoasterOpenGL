#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/common.hpp>
#include "../../Source/Model.h"
#include <vector>
#include "../../Source/CubeModel.h"

class BoundingBox : public Model
{
private:
	struct Vertex
	{
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec3 color;
	};
	std::vector<Vertex> vertexBuffer;

public:
	BoundingBox(std::vector<Vertex> vertexBuffer);
	BoundingBox(Model * parent, bool getScalingFromParent, glm::vec3 size);
	void createBoundingBox();
	void CalculateBoundingBoxCoordinates();
	bool HasObjectCollidedWithAnotherAABB(BoundingBox* OtherBox);
};