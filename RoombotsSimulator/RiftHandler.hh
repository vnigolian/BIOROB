/**
@author Valentin NIGOLIAN
valentin.nigolian@epfl.ch
Fall 2015
*/
#pragma once
#include "common.hh"
#include "DepthBuffer.hh"
#include "TextureBuffer.hh"

/**This class makes the Rift much simpler to use.
  All that must be done is first initialise the Rift with 'Init(DisplayFunction)', where 'DisplayFunction'
  is the function that draws what we want to display on the Rift and then call 'DisplayOnRift' when we want 
  to display something on the Rift.
  To take its orientation into account when drawing the scene (in the DisplayFunction passed in argument in 'Init()'), 
  one must can use the 'ovrViewProjMatrix()' or 'glmViewProjMatrix()' methods to get the view-projection matrix 
  in the form of a OVR::Matrix4f or a glm::mat4 matrix.
  The OVR::Matrix4f is how it is created by the Rift's SDK but the glm::mat4 one is easier to use with OpenGL
*/

typedef void(*DisplayFunction)();//a display function does not take any argument and returns nothing

class RiftHandler
{
	OVR::Matrix4f    d_viewProjMatrix;     ///<THE viewProj matrix representing the orientation of the HMD
	ovrHmd           d_hmd = nullptr;      ///<The code object representing the Rift's HMD
	ovrTrackingState d_trackingState;      ///<The tracking state of the HMD
	bool             d_isVisible = false;  ///<Keeps the rendering to be displayed while the Rift hasn't been initialized
	ovrEyeRenderDesc d_EyeRenderDesc[2];   ///<Store all the rendering information for both eyes
	TextureBuffer*   d_eyeRenderTexture[2];///<The textures where the image from both eyes will be stored
	DepthBuffer*     d_eyeDepthBuffer[2];  ///<The buffer where the depth information from both eyes will be stored
	GLuint           d_mirrorFBO = 0;      ///<The FBO for the mirror display
	ovrGLTexture*    d_mirrorTexture;      ///<The texture for the mirror display
	DisplayFunction  d_displayFunction;    ///<the function that draws what will be displayed on the Rift's screen

public:
	/**displays the rendering done in 'displayFunction' on the Rift's screen*/
	void DisplayOnRift();

	/**Initializes the Rift
	  \arg DisplayFunction  the function that will do the actual rendering and will draw what
	  is to be displayed on the Rift's screen*/
	void Init(DisplayFunction);

	/**Returns the view projection matrix that is built based on the Rift's orientation*/
	OVR::Matrix4f ovrViewProjMatrix();

	/**Same as 'ovrProjViewMatrix()' but returns a glm::mat4 instead*/
	glm::mat4 glmViewProjMatrix();

	/**Returns the width of the Rift's resolution*/
	unsigned int ResolutionWidth();

	/**Returns the height of the Rift's resolution*/
	unsigned int ResolutionHeight();

	/**Destroys and shuts the Rift virtual object down*/
	void CleanUp();
};



