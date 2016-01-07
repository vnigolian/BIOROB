/**
	@author Valentin NIGOLIAN
	valentin.nigolian@epfl.ch
	Fall 2015
*/

///This file simply regroups includes of external libraries used in most other files to leave said files clean 
#pragma once

#include "Libraries\glew\glew.h" //for OpenGL graphics operations
#include "Libraries\glew\wglew.h" //for OpenGL graphics operations
#include "Libraries\freeglut\freeglut.h" //for window and OpenGL context creation
#include "glm\glm.hpp" //for mathematical operations used in OpenGL
#include "glm\gtc\matrix_transform.hpp"//for transformations (matrices)
#include "glm\gtx\transform.hpp" 
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
#include <ctime>


#include "Libraries\Leap\Leap.h"


///All the following macros are in meters

#define EYES_POSITION 1.2f ///< The vertical position of the camera 
#define MODULE_SIZE 0.12f ///<The size of a a half of a Roombots module
#define ROOM_SIZE 5.0f ///<The size of the room
#define BUTTON_SIZE 0.5f ///<The size of a button
#define BUTTON_SEPARATION 1.0f ///<The horizontal distance between two buttons
#define BUTTON_UP_START 1.8f ///<The vertical point where the buttons are positioned 
#define BUTTON_DEPTH_OFFSET -4.5f ///<The depth point where the buttons are positioned
#define BUTTON_RIGHT_START 2.0f ///<The horizontal point from where the buttons are drawn
#define LEAP_POINTER_SIZE 1.0f ///<The size of the LeapmotionPointer
#define COORDINATE_SYSTEM_SCALE_CONVERSION 0.005f ///<A conversion factor to scale the data 
                                                  ///<coming from the Leapmotion device
                                                  ///<to fit the Room-View mode characteristics
#define BOX_COORDINATE_SYSTEM_SCALE_CONVERSION 0.016f ///<A conversion factor to scale the data 
													  ///<coming from the Leapmotion device
													  ///<to fit the Box-View mode characteristics
#define PINCHING_LIMIT 0.7f ///<The minimal pinching value to consider that the hand is pinching
#define DRAG_RADIUS 0.4f ///<The minimal distance to grab a Structure
#define TRASH_CAN_SIZE 2.0f///<The size of the TrashCan





