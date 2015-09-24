#include "Model.hh"


class Cube : public Model {


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
public:
	Cube* copy() const;

protected:
	virtual void SetVertices(std::vector<vec3> *vertices);
	virtual void SetUVs(std::vector<vec2> *uvs);

};
