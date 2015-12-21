#pragma once

#include "Model.hh"
#include <string>

class OBJModel : public Model
{
public :
	OBJModel(const std::string OBJFilename,
		const char* vShaderFileName,
		const char* fShaderFileName,
		const char* textureFileName,
		const glm::vec4& color);

	OBJModel* copy() const;

protected:
	virtual void SetVertices(std::vector<glm::vec3> *vertices);
	virtual void SetUVs(std::vector<glm::vec2> *uvs);
	
	//void setOBJfile(std::string filename);

	const std::string _objfilename;
};



