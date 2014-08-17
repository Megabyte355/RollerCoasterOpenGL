#include"mesh.h"
#include<sstream>

mesh::mesh(vector<vertexData>* vd, vector<unsigned int>* id, vector<textureData>* td)
{
	data = *vd;
	indices= *id;
	if(td)
		textures = *td;

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, data.size()* sizeof(vertexData), &data[0], GL_STATIC_DRAW);

	glGenBuffers(1, &IND);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IND);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()* sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

mesh::~mesh()
{
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &IND);
}

void mesh::draw(unsigned int programId)
{
	//attribute vec3 vertex
	GLuint vertex = glGetAttribLocation(programId, "vertex"); //0
	//GLuint normal = glGetAttribLocation(programId, "normal"); //1
	//GLuint tangent = glGetAttribLocation(programId, "tangent"); //2
	//GLuint color = glGetAttribLocation(programId, "color"); //3
	GLuint UV = glGetAttribLocation(programId, "UV"); //4

	//texture0
	//texture1...
	for(int i=0; i<textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0+i);
		glBindTexture(GL_TEXTURE_2D, textures[i].id);
		std::stringstream sstm;
		sstm << "texture" << i;// << "0";
		glUniform1i(glGetUniformLocation(programId, &sstm.str()[0]), i);
	}

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IND);

	glEnableVertexAttribArray(vertex);
	glVertexAttribPointer(vertex, 3, GL_FLOAT, GL_FALSE, sizeof(vertexData), (void*)0);

	/*glEnableVertexAttribArray(normal);
	glVertexAttribPointer(normal, 3, GL_FLOAT, GL_FALSE, sizeof(vertexData), (void*)(sizeof(glm::vec3)));

	glEnableVertexAttribArray(tangent);
	glVertexAttribPointer(tangent, 3, GL_FLOAT, GL_FALSE, sizeof(vertexData), (void*)(2*sizeof(glm::vec3)));

	glEnableVertexAttribArray(color);
	glVertexAttribPointer(color, 3, GL_FLOAT, GL_FALSE, sizeof(vertexData), (void*)(3*sizeof(glm::vec3)));
*/
	glEnableVertexAttribArray(UV);
	glVertexAttribPointer(UV, 2, GL_FLOAT, GL_FALSE, sizeof(vertexData), (void*)(4*sizeof(glm::vec3)));

	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0); 
	
	glDisableVertexAttribArray(vertex);
	/*glDisableVertexAttribArray(tangent);
	glDisableVertexAttribArray(normal);
	glDisableVertexAttribArray(color);*/
	glDisableVertexAttribArray(UV);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);	
}