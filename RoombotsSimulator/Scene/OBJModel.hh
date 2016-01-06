/*
@author Valentin NIGOLIAN
valentin.nigolian@epfl.ch
Fall 2015
*/
#pragma once

#include "Model.hh"
#include <string>

/**
	An OBJModel is a Model that gets its vertices from a .obj file.
	.obj (wavefront) files are standard graphics models files and are pretty easy to parse.
	But they also contain shading and texturing information that are not used in this software.
	Furthermore, .obj files sometimes contain polygons which would be ignored by the parser.
	However, quads would be interpreted as two triangles

	This class allows to use complex models pretty easily.
*/
class OBJModel : public Model
{
public :
	/*Same constructor as the Model class but with the .obj filename added to it*/
	OBJModel(const std::string OBJFilename,
		const char* vShaderFileName,
		const char* fShaderFileName,
		const char* textureFileName,
		const glm::vec4& color);

protected:
	/*This method parses the .obj filename of the OBJModel and creates the
	corresponding vertices */
	virtual void SetVertices(std::vector<glm::vec3> *vertices);

	virtual void SetUVs(std::vector<glm::vec2> *uvs);
	
	const std::string _objfilename;
};



