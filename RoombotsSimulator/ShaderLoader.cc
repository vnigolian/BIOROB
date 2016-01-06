#include "ShaderLoader.hh"

/*NOTES ABOUT USING SHADERS	

In order to use shaders, we must take a certain number of well-defined steps :

	1. create the shader objects
	2. send the source to OpenGL
	3. compile the shaders
	4. attach the shaders to the programm object
	5. link the program
	6. bind the program ready for use
	7. send uniforms and vertex atributes to the shaders
	8. render the objects that use the program

	steps 1 to 3 are done in 'CreateShaders', steps 4 and 5 are done in 'CreateProgram'

*/
using namespace Core;

std::string ShaderLoader::ReadShader(const char *filename)
{
	
	std::string shaderCode;//this string that will contain the glsl program
	std::ifstream file(filename, std::ios::in);//opens a file stream to read the glsl file

	//test the file and its readability
	if (!file.good())
	{
		std::cout << "Can't read glsl file " << filename << std::endl;
		return "invalidShader";
	}
	//actual reading of the file
	file.seekg(0, std::ios::end);//puts the pointer at the end of the file
	shaderCode.resize((unsigned int)file.tellg());//resize our string so it matches the size of the file
	file.seekg(0, std::ios::beg);//puts the poiter at the beginning of the file
	file.read(&shaderCode[0], shaderCode.size());//copies the content of the file in our string
	file.close();
	return shaderCode;
}

GLuint ShaderLoader::CreateShader(GLenum shaderType, 
	                              std::string source, 
								  char* name)
{
	GLint compileResult = 0; 

	//create the shader
	GLuint shader = glCreateShader(shaderType);
	const char *p_shaderCode = source.c_str();
	const int shaderCodeSize = source.size();

	//send the source to OpenGL
	glShaderSource(shader, 1, &p_shaderCode, &shaderCodeSize);
	//compile the shader
	glCompileShader(shader);
	//as 'glCompileShader' doesn't return anything, we use this next line to
	//know if the compilation was successful and store the information in 'compileResult'
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileResult);

	//if the the shader compilation went wrong, we handle the error
	if (compileResult == GL_FALSE)
	{

		int infoLogLength = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
		std::vector<char> shader_log(infoLogLength);
		glGetShaderInfoLog(shader, infoLogLength, NULL, &shader_log[0]);
		std::cout << "ERROR compiling shader: " << name << std::endl << &shader_log[0] << std::endl;
		return 0;
	}
	return shader;
}

GLuint ShaderLoader::CreateProgram(const char* vShaderFilename,
	                               const char* fShaderFilename)
{

	//use our previously defined method to read the shader files and save the code
	std::string vShaderCode = ReadShader(vShaderFilename);
	if (vShaderCode == "invalidShader")
	{
		std::cout << "invalid vertex shader, using the default one" << std::endl;
		vShaderCode = DefaultVertexShader();
	}

	std::string fShaderCode = ReadShader(fShaderFilename);
	if (fShaderCode == "invalidShader")
	{
		std::cout << "invalid fragment shader, using the default one" << std::endl;
		fShaderCode = DefaultFragmentShader();
	}
	//use our previously defined method to create the two shaders
	GLuint vShader = CreateShader(GL_VERTEX_SHADER, vShaderCode, "vertex shader");
	GLuint fShader = CreateShader(GL_FRAGMENT_SHADER, fShaderCode, "fragment shader");

	int linkResult = 0;
	//create the program handle
	GLuint program = glCreateProgram();
	
	//attach both shaders
	glAttachShader(program, vShader);
	glAttachShader(program, fShader);

	//link the program
	glLinkProgram(program);
	//and get the linking status
	glGetProgramiv(program, GL_LINK_STATUS, &linkResult);

	//this is similar to what we did in 'CreateShader'
	if (linkResult == GL_FALSE)
	{

		int info_log_length = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_log_length);
		std::vector<char> program_log(info_log_length);
		glGetProgramInfoLog(program, info_log_length, NULL, &program_log[0]);
		std::cout << "Shader Loader : LINK ERROR" << std::endl << &program_log[0] << std::endl;
		return 0;
	}
	return program;
}

std::string ShaderLoader::DefaultVertexShader()
{
	return "#version 330 core \n uniform mat4 MVP; \n in vec3 vpoint; \n in vec2 vtexcoord; \n out vec2 uv; \n void main(){ \n gl_Position = MVP * vec4(vpoint, 1); \n uv = vtexcoord; \n }";
}

std::string ShaderLoader::DefaultFragmentShader()
{
	return "#version 330 core \n uniform sampler2D tex; \n in vec2 uv; \n out vec4 color; \n void main(){ \n color = vec4(1.0, 1.0, 1.0, 1.0); \n}";
}