/*
	@author Valentin NIGOLIAN
	valentin.nigolian@epfl.ch
	Fall 2015
*/

//This file simply regroups includes used in most other files to leave said files cleaner 
#pragma once

#include "Libraries\glew\glew.h" //for OpenGL graphics operations
#include "Libraries\glew\wglew.h" //for OpenGL graphics operations
#include "Libraries\freeglut\freeglut.h" //for window and OpenGL context creation
#include "glm\glm.hpp" //for mathematical operations used in OpenGL
#include "glm\gtc\matrix_transform.hpp"//for transformations (matrices)
#include "glm\gtx\transform.hpp" //
#include "glm\gtx\euler_angles.hpp"
#include "Libraries\soil\SOIL.h"//for texture loading

#include "Libraries\wgl\wglext.h"
#include "Libraries\wgl\glext.h"

#include "Libraries\OVR\OVR_CAPI_GL.h"//Oculus' library
#include "Libraries\OVR\Extras\OVR_Math.h"

#include <Windows.h>
#include "Libraries\wgl\wglext.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>

#include "Libraries\Leap\Leap.h"


#define EYES_POSITION 1.2f
#define MODULE_SIZE 0.12f
#define ROOM_SIZE 5.0f




