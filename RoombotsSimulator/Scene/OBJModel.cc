#include "OBJModel.hh"

OBJModel::OBJModel(const std::string OBJFilename,
	const char* vShaderFileName,
	const char* fShaderFileName,
	const char* textureFileName,
	const glm::vec4& color) : _objfilename(OBJFilename), Model(vShaderFileName, fShaderFileName, textureFileName, color) {
	Init();
}


OBJModel* OBJModel::copy() const
{
	OBJModel* p_newOBJModel = new OBJModel(_objfilename,_vShader, _fShader, _texture, _color);
	p_newOBJModel->SetModelMatrix(_M);
	return p_newOBJModel;
}


/*void OBJModel::setOBJfile(std::string filename)
{
	_objfilename = filename;
}*/

void OBJModel::SetVertices(std::vector<glm::vec3> *vertices)
{
	std::ifstream in;
	in.open(_objfilename.c_str());
	if (in.fail())
	{
		std::cerr << "ERROR - Couldn't open "<<_objfilename<<" Model file " << std::endl;
	}
	else
	{
		std::vector<glm::vec3> newVertices;

		while (!in.eof())
		{
			std::string c = "";
			std::string i = "";
			double x, y, z;

			while (c != "f")
			{
				if (c == "v")
				{
					in >> x;
					in >> y;
					in >> z;
					newVertices.push_back(glm::vec3(x, z, y));
				}
				in >> c;
			}
			while (c == "f")
			{
				in >> c;
				//int index;
				std::vector<unsigned int> faceIndices;
				while (c != "f"&& !in.eof())
				{
					std::string acc = "";
					size_t i = 0;
					while (c[i] != '/' && i < c.length())
					{
						acc += c[i];
						i++;
					}
					faceIndices.push_back(stoi(acc));
					in >> c;
				}
				//we add the triangle's vertices to the model's vertices
				for (size_t i = 0; i < 3; i++)
				{
					vertices->push_back(newVertices[faceIndices[i] - 1]);
				}
				//if the face has 4 vertices it means it's a quad and we add another triangle
				if (faceIndices.size() == 4)
				{
					vertices->push_back(newVertices[faceIndices[0] - 1]);
					vertices->push_back(newVertices[faceIndices[3] - 1]);
					vertices->push_back(newVertices[faceIndices[2] - 1]);
				}
			}
		}
	}
	//std::cout << "finished loading  with " << vertices->size() << std::endl;
	in.close();
}

void OBJModel::SetUVs(std::vector<glm::vec2> *uvs){}