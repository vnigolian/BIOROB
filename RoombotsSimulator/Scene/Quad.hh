#pragma once

#include "Model.hh"


class Quad : public Model {

public:
	Quad* copy() const;

protected:
	virtual void SetVertices(std::vector<vec3> *vertices);
	virtual void SetUVs(std::vector<vec2> *uvs);

};
