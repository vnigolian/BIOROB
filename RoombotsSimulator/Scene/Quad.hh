#pragma once

#include "Model.hh"


class Quad : public Model {

public:
	Quad(const std::string vShaderFileName,
		const std::string fShaderFileName,
		const std::string textureFileName,
		const glm::vec4& color) : Model(vShaderFileName, fShaderFileName, textureFileName, color){}

	Quad(const char* vShaderFileName,
		const char* fShaderFileName,
		const char* textureFileName,
		const glm::vec4& color) : Model(vShaderFileName, fShaderFileName, textureFileName, color) {}

	Quad* copy() const;

protected:
	virtual void SetVertices(std::vector<glm::vec3> *vertices);
	virtual void SetUVs(std::vector<glm::vec2> *uvs);

};
