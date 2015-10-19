#pragma once

#include "Model.hh"
#include <string>

class OBJModel : public Model
{
public :

	OBJModel* copy() const;
	void setOBJfile(std::string filename);

protected:
	virtual void SetVertices(std::vector<glm::vec3> *vertices);
	virtual void SetUVs(std::vector<glm::vec2> *uvs);
	
	std::string _objfilename;
};



