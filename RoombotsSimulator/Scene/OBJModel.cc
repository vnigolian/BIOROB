#include "OBJModel.hh"

OBJModel::OBJModel(const std::string OBJFilename,
	const char* vShaderFileName,
	const char* fShaderFileName,
	const char* textureFileName,
	const glm::vec4& color) : _objfilename(OBJFilename), Model(vShaderFileName, fShaderFileName, textureFileName, color) {
	Init();
}


void OBJModel::SetVertices(std::vector<glm::vec3> *vertices)
{
	bool error = false;

	std::ifstream in;
	in.open(_objfilename.c_str());
	
	if (in.fail())
	{
		std::cerr << "ERROR - Couldn't open "<<_objfilename<<" Model file " << std::endl;
		error = true;
	}
	else
	{
		std::vector<glm::vec3> newVertices;

		while (!in.eof() && ! error)
		{
			std::string c = "";
			std::string i = "";
			double x, y, z;

			//first, we look for the beginning of the declaration of faces
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
			while (c == "f" && ! error)
			{
				in >> c;
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
					try
					{
						faceIndices.push_back(stoi(acc));
					}
					catch (std::invalid_argument arg)
					{
						std::cerr << "Error when reading " << _objfilename << " : " << arg.what() << std::endl;
						std::cerr << "This probably comes from a invalid-format .obj file. Check out the documentation for more information" << std::endl;
						error = true;
					}
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
		if (error)
		{
			std::cout << "Loading from " << _objfilename << " is done but there has been an error and the model might not be complete" << std::endl;
		}
		else
		{
			std::cout << "Finished loading OBJModel from " << _objfilename << " with " << vertices->size() << " vertices.";
		}
	}

	in.close();
}

void OBJModel::SetUVs(std::vector<glm::vec2> *uvs){}