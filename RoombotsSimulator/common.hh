//This file simply regroups includes used in most other files to leave said files cleaner 
#pragma once

#include "Libraries\glew\glew.h" //for OpenGL graphics operations
#include "Libraries\glew\wglew.h" //for OpenGL graphics operations
#include "Libraries\freeglut\freeglut.h" //for window and OpenGL context creation
#include "glm\glm.hpp" //for mathematical operations used in OpenGL
#include "glm\gtc\matrix_transform.hpp"//for transformations (matrices)
#include "glm\gtx\transform.hpp" //
#include "Libraries\soil\SOIL.h"//for texture loading

#include "Libraries\wgl\wglext.h"
#include "Libraries\wgl\glext.h"

#include "Libraries\OVR\OVR_CAPI_GL.h"//Oculus' library
#include "Libraries\OVR\Extras\OVR_Math.h"

#include <Windows.h>
#include "Libraries\wgl\wglext.h"

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>



//those typedefs simplify further code writing
//NOTE : See if doesn't make any problem regarding name conflicts
typedef glm::mat4 mat4;
typedef glm::vec3 vec3;
typedef glm::vec2 vec2;

