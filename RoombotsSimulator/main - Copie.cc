
#include "common.hh"
#include "ShaderLoader.hh"
#include "Models\Quad.hh"
#include "Models\Skybox.hh"
#include "DepthBuffer.hh"
#include "TextureBuffer.hh"

using namespace Core;
//using namespace OVR;
//using namespace std;
//using namespace glm;

Quad floor_quad;
Skybox sky;

unsigned int width = 0;
unsigned int height = 0;

mat4 projectionMatrix;
mat4 viewMatrix;
mat4 worldMatrix;

ovrHmd hmd = nullptr;
ovrTrackingState trackingState;
bool isVisible = false;
ovrEyeRenderDesc EyeRenderDesc[2];//Store all the rendering information for both eyes
TextureBuffer * eyeRenderTexture[2];//The textures where the image from both eyes will be stored
DepthBuffer   * eyeDepthBuffer[2];//The buffer where the depth information from both eyes will be stored
GLuint mirrorFBO = 0; //The FBO for the mirror display
ovrGLTexture* mirrorTexture; //The texture for the mirror display


// Gets called when the windows is resized.
void Resize(int w, int h)
{
	//We want the window to be fixed-size (adapted to the Rift's display)
	glutReshapeWindow(width,height);
}

glm::mat4 OVR_Mat4_to_GLM_mat4(OVR::Matrix4f sourceMatrix)
{
	glm::mat4 newMatrix = mat4(0.0f);
	for (unsigned int i(0); i < 4; i++)
	{
		for (unsigned int j(0); j < 4; j++)
		{
			newMatrix[i][j] = sourceMatrix.M[j][i];
		}
	}
	return newMatrix;
}


void Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	
	//Distance between the center of the HMD and the eyes
	ovrVector3f ViewOffset[2] = { EyeRenderDesc[0].HmdToEyeViewOffset, EyeRenderDesc[1].HmdToEyeViewOffset };
	//Pose of the eyes
	ovrPosef EyeRenderPose[2];
	//Timing used for the rendering. 
	//    See documentation for more details about the use of time in the Rift's rendering process
	ovrFrameTiming frameTiming = ovrHmd_GetFrameTiming(hmd, 0);
	//Pose of the HMD
	ovrTrackingState hmdState = ovrHmd_GetTrackingState(hmd, frameTiming.DisplayMidpointSeconds);
	//offset eye poses based on headPose --> WARNING
	ovr_CalcEyePoses(hmdState.HeadPose.ThePose, ViewOffset, EyeRenderPose);
	
	if (isVisible)
	{
		for (int eye = 0; eye<2; eye++)
		{
			// Increment to use next texture, just before writing
			eyeRenderTexture[eye]->TextureSet->CurrentIndex = (eyeRenderTexture[eye]->TextureSet->CurrentIndex + 1) % eyeRenderTexture[eye]->TextureSet->TextureCount;
			
			// Switch to eye render target
			eyeRenderTexture[eye]->SetAndClearRenderSurface(eyeDepthBuffer[eye]);
			
			OVR::Matrix4f rotationMatrix = OVR::Matrix4f(EyeRenderPose[eye].Orientation);
			OVR::Vector3f cam_up = rotationMatrix.Transform(OVR::Vector3f(0, 1, 0));
			OVR::Vector3f cam_look = rotationMatrix.Transform(OVR::Vector3f(0, 0, -1));
			OVR::Vector3f cam_pos = OVR::Vector3f(0.0, 0.0, 0.0);

			OVR::Matrix4f view = OVR::Matrix4f::LookAtRH(cam_pos, cam_look, cam_up);
			OVR::Matrix4f proj = ovrMatrix4f_Projection(hmd->DefaultEyeFov[eye], 0.2f, 1000.0f, ovrProjection_RightHanded);

			// Render world
			mat4 VP = OVR_Mat4_to_GLM_mat4(proj*view);
			floor_quad.Draw(VP);
			sky.Draw(VP);

			// Avoids an error when calling SetAndClearRenderSurface during next iteration.
			// Without this, during the next while loop iteration SetAndClearRenderSurface
			// would bind a framebuffer with an invalid COLOR_ATTACHMENT0 because the texture ID
			// associated with COLOR_ATTACHMENT0 had been unlocked by calling wglDXUnlockObjectsNV.
			eyeRenderTexture[eye]->UnsetRenderSurface();
			}
		}

		// Set up positional data.
		ovrViewScaleDesc viewScaleDesc;
		viewScaleDesc.HmdSpaceToWorldScaleInMeters = 1.0f; //sets the scale between real world meters and virtual meters
		viewScaleDesc.HmdToEyeViewOffset[0] = ViewOffset[0];//Here, we set 
		viewScaleDesc.HmdToEyeViewOffset[1] = ViewOffset[1];

		ovrLayerEyeFov ld;
		ld.Header.Type = ovrLayerType_EyeFov;
		ld.Header.Flags = ovrLayerFlag_TextureOriginAtBottomLeft;   // Because OpenGL.

		for (int eye = 0; eye < 2; eye++)
		{
			ld.ColorTexture[eye] = eyeRenderTexture[eye]->TextureSet;
			ld.Viewport[eye] = OVR::Recti(eyeRenderTexture[eye]->GetSize());
			ld.Fov[eye] = hmd->DefaultEyeFov[eye];
			ld.RenderPose[eye] = EyeRenderPose[eye];
		}

		ovrLayerHeader* layers = &ld.Header;
		ovrResult result = ovrHmd_SubmitFrame(hmd, 0, &viewScaleDesc, &layers, 1);
		isVisible = OVR_SUCCESS(result);

		// Blit mirror texture to back buffer
		glBindFramebuffer(GL_READ_FRAMEBUFFER, mirrorFBO);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
		GLint w = mirrorTexture->OGL.Header.TextureSize.w;
		GLint h = mirrorTexture->OGL.Header.TextureSize.h;
		glBlitFramebuffer(0, h, w, 0,
			0, 0, w, h,
			GL_COLOR_BUFFER_BIT, GL_NEAREST);
		glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);

	glutSwapBuffers();//switch between the two buffers
	
}




void RiftInit()
{
	// Initialise the oculus VR SDK
	if (ovr_Initialize(nullptr) != ovrSuccess)
	{
		std::cerr << "libOVR couldn't be initialized\n";
	}
	// Create the Head Mounted Display's virtual object
	ovrResult result = ovrHmd_Create(0, &hmd);
	
	//If no HMD is detected, a virtual one is created, allowing to continue the program
	//and still display something
	//It is useful for debugging purpose
	if (!OVR_SUCCESS(result))
	{
		std::cerr << "No Oculus HMD detected, creating a virtual one\n";
		result = ovrHmd_CreateDebug(ovrHmd_DK2, &hmd);
	}
	//If even a virtual HMD cannot be created, there's probably 
	//something wrong with the Oculus runtime
	if (!OVR_SUCCESS(result))
	{
		std::cerr << "Oculus Rift not detected. You might want to install it\n";
	}

	//This sets the mirror window's size
	//The mirror window is the one that mirrors the Rift's display on the regular screen
	ovrSizei windowSize = { hmd->Resolution.w / 2, hmd->Resolution.h / 2 };
	width = hmd->Resolution.w/2;
	height = hmd->Resolution.h/2;
	glutReshapeWindow(width, height);

	//Since the Rift's display is based on stereo view, we have to render the scene twice,
	//once for each eye. This is why we will often make a 2-iterations loop, one iteration for each eye
	//Here, we create two textures and two depth buffers to store the rendering for both eyes
	for (int i = 0; i<2; i++)
	{
		ovrSizei idealTextureSize = ovrHmd_GetFovTextureSize(hmd, (ovrEyeType)i, hmd->DefaultEyeFov[i], 1);
		eyeRenderTexture[i] = new TextureBuffer(hmd, true, true, idealTextureSize, 1, NULL, 1);
		eyeDepthBuffer[i] = new DepthBuffer(eyeRenderTexture[i]->GetSize());
	}

	//Creates the mirror texture and an FBO used to mirror the Rift's display onto the regular screen
	ovrHmd_CreateMirrorTextureGL(hmd, GL_RGBA, windowSize.w, windowSize.h, (ovrTexture**)&mirrorTexture);
	
	//Generates and binds the FrameBuffer Object used to render the mirror texture
	glGenFramebuffers(1, &mirrorFBO);
	glBindFramebuffer(GL_READ_FRAMEBUFFER, mirrorFBO);
	glFramebufferTexture2D(GL_READ_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mirrorTexture->OGL.TexId, 0);
	glFramebufferRenderbuffer(GL_READ_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, 0);
	glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);

	//sets up the rendering information of both eyes based on the HMD's characteristics and configuration
	EyeRenderDesc[0] = ovrHmd_GetRenderDesc(hmd, ovrEye_Left, hmd->DefaultEyeFov[0]);
	EyeRenderDesc[1] = ovrHmd_GetRenderDesc(hmd, ovrEye_Right, hmd->DefaultEyeFov[1]);

	ovrHmd_SetEnabledCaps(hmd, ovrHmdCap_LowPersistence | ovrHmdCap_DynamicPrediction);

	//Starts the sensor's tracking
	ovrHmd_ConfigureTracking(hmd, ovrTrackingCap_Orientation | ovrTrackingCap_MagYawCorrection |
		ovrTrackingCap_Position, 0);

	//The VSync must be turned off in order for the compositor to work properly
	//Since this is related to the system on which the program is running, the function to use differs
	//between Windows and OSX. ubuntu does not fully work on Ubuntu so there is no need to worry about that yet
	wglSwapIntervalEXT(0); // WARNING !! THIS ONLY WORKS WITH WINDOWS 
	//glxSwapIntervalEXT(0); //this might be the right call for OS X --> it will be tested
	
	//now that everything is set up, we can start rendering
	isVisible = true;
}

void Init()
{
	glEnable(GL_DEPTH_TEST);

	floor_quad.Init("Shaders/quad_vshader.glsl", "Shaders/quad_fshader.glsl", "Textures/floor2.png");
	floor_quad.SetModelMatrix(glm::scale(mat4(1.0f), vec3(10.0))*glm::translate(mat4(1.0f), vec3(0.0f, -0.5f, -1.0f)));

	sky.Init("Shaders/sky_vshader.glsl", "Shaders/sky_fshader.glsl", "Textures/skybox_texture.jpg");
	sky.SetModelMatrix(glm::scale(mat4(1.0f), vec3(50.0f)));

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//<------- LINE MODE

	RiftInit();
}

void CleanUp()
{
	floor_quad.CleanUp();
	sky.CleanUp();
	ovrHmd_Destroy(hmd);
	ovr_Shutdown();
}

/*
this method allows us to have control over the main OpenGL context loop.
we call one iteration of the loop ourself
*/
void MainLoop()
{
	while (true)
	{
		glutMainLoopEvent();//executes one iteration of the OpenGL main loop
		Display();//we call display at every iteration so that we update the view matrix depending on the Oculus' position
	}
}

int main(int argc, char **argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);//allows to use depth, color and double buffering
	glutInitWindowPosition(500, 200);
	glutInitWindowSize(0, 0); //it will be resized in Init();
	glutCreateWindow("RoomBots Simulator");

	GLenum err = glewInit();
	if (!err)
	{
		fprintf(stdout, "GLEW init error : %s\n", glewGetErrorString(err));
	}

	fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

	Init();
	// register callbacks
	glutDisplayFunc(Display);//sets 'Display' as the function to call when displaying
	glutReshapeFunc(Resize);//sets 'Resize' as the function to cass when resizing

	MainLoop();//starts the main loop

	CleanUp();//cleans up everything
	return 0;
}
