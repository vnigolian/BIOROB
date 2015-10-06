#include "RiftHandler.hh"

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

unsigned int RiftHandler::ResolutionWidth()
{
	return hmd->Resolution.w;
}
unsigned int RiftHandler::ResolutionHeight()
{
	return hmd->Resolution.h;
}


OVR::Matrix4f RiftHandler::ovrViewProjMatrix()
{
	return viewProjMatrix;
}

glm::mat4 RiftHandler::glmViewProjMatrix()
{
	return OVR_Mat4_to_GLM_mat4(viewProjMatrix);
}

void RiftHandler::Init(DisplayFunction disFunc)
{
	//sets the display function as the one passed in argument
	displayFunction = disFunc;

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
	ovrSizei windowSize = { hmd->Resolution.w / 2, hmd->Resolution.h / 2 };
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


void RiftHandler::DisplayOnRift()
{
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
			OVR::Matrix4f proj = ovrMatrix4f_Projection(hmd->DefaultEyeFov[eye], 0.001f, 1000.0f, ovrProjection_RightHanded);

			// Render world
			viewProjMatrix = proj*view;

			displayFunction();//calls the display function

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

}

void RiftHandler::CleanUp()
{
	ovrHmd_Destroy(hmd);
	ovr_Shutdown();
}