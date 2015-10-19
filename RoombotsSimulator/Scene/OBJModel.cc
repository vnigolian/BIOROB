#include "OBJModel.hh"


OBJModel* OBJModel::copy() const
{
	OBJModel* p_newOBJModel =  new OBJModel;

	p_newOBJModel->setOBJfile(_objfilename);
	p_newOBJModel->Init(_vShader, _fShader, _texture);
	p_newOBJModel->SetModelMatrix(_M);
	return p_newOBJModel;
}


void OBJModel::setOBJfile(std::string filename)
{
	_objfilename = filename;
}

void OBJModel::SetVertices(std::vector<glm::vec3> *vertices)
{
	std::ifstream in;
	in.open(_objfilename.c_str());
	if (in.fail())
	{
		std::cout << "ERROR specified file not found" << std::endl;
	}
	else
	{
		std::vector<glm::vec3> newVertices;

		while (!in.eof())
		{
			std::string c;
			const char* p(&c[0]);
			std::string i;
			double x, y, z;
			std::string objectname;
			std::string curligne;

			while (c != "o"){ in >> c; }
			in >> objectname;
			std::cout << objectname << std::endl;

			while (c != "f")
			{
				if (c == "v")
				{
					in >> x;
					in >> y;
					in >> z;
					newVertices.push_back(glm::vec3(x, z, y));
				}

				//std::cout << "v = " << x << " " << y << " " << z << std::endl;

				in >> c;
			}
			while (c == "f")
			{
				in >> c;
				int index;
				std::vector<unsigned int> faceIndices;
				while (c != "f"&& !in.eof())
				{
					p = &c[0];
					faceIndices.push_back(atoi(p));
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
	std::cout << "finished loading" << std::endl;
	std::cout << " with " << vertices->size() << std::endl;
	in.close();
}

void OBJModel::SetUVs(std::vector<glm::vec2> *uvs){}