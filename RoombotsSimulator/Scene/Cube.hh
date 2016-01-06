/*
@author Valentin NIGOLIAN
valentin.nigolian@epfl.ch
Fall 2015
*/
#pragma once

#include "Model.hh"

/*The vertices of this class define a cube and the
texture coordinates are chosen so that it works with cubemap texture looking like this :
______
¦  ##  ¦
¦  ##  ¦
¦######¦
¦__##__¦

where every ## is a face of the cube. More precisely :
______
¦  bb  ¦
¦  rr  ¦
¦uuffdd¦
¦__ll__¦

where ff is the front face, bb the back face,
uu the up face, dd the down face,
rr the right face and ll the left face
*/
class Cube : public Model {

public:
	Cube(const std::string vShaderFileName,
		const std::string fShaderFileName,
		const std::string textureFileName,
		const glm::vec4& color) : Model(vShaderFileName, fShaderFileName, textureFileName, color){
		Init();
	}

	Cube(const char* vShaderFileName,
		const char* fShaderFileName,
		const char* textureFileName,
		const glm::vec4& color) : Model(vShaderFileName, fShaderFileName, textureFileName, color) {
		Init();
	}
	
protected:
	/*Creates and adds vertices to the Model to create a one-meter cube*/
	virtual void SetVertices(std::vector<glm::vec3> *vertices);
	virtual void SetUVs(std::vector<glm::vec2> *uvs);

};
