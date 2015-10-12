#pragma once

#include "Model.hh"


class Quad : public Model {

public:
	Quad* copy() const;

protected:
	virtual void SetVertices(std::vector<glm::vec3> *vertices);
	virtual void SetUVs(std::vector<glm::vec2> *uvs);

};
