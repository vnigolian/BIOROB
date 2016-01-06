/**********************************************************************
Most of the code from this file comes from the OculusRoomTiny (GL) demo 
from the Oculus' SDK and therefore the following is applied :

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http ://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

************************************************************************/
#include "RiftHandler.hh"

glm::mat4 OVR_Mat4_to_GLM_mat4(OVR::Matrix4f sourceMatrix)
{
	glm::mat4 newMatrix = glm::mat4(0.0f);
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
	return d_hmd->Resolution.w;
}
unsigned int RiftHandler::ResolutionHeight()
{
	return d_hmd->Resolution.h;
}


OVR::Matrix4f RiftHandler::ovrViewProjMatrix()
{
	return d_viewProjMatrix;
}

glm::mat4 RiftHandler::glmViewProjMatrix()
{
	return OVR_Mat4_to_GLM_mat4(d_viewProjMatrix);
}

void RiftHandler::Init(DisplayFunction disFunc)
{
	//sets the display function as the one passed in argument
	d_displayFunction = disFunc;

	// Initialise the oculus VR SDK
	if (ovr_Initialize(nullptr) != ovrSuccess)
	{
		std::cerr << "libOVR couldn't be initialized\n";
	}
	// Create the Head Mounted Display's virtual object
	ovrResult result = ovrHmd_Create(0, &d_hmd);

	//If no HMD is detected, a virtual one is created, allowing to continue the program
	//and still display something
	//It is useful for debugging purpose
	if (!OVR_SUCCESS(result))
	{
		std::cerr << "No Oculus HMD detected, creating a virtual one\n";
		result = ovrHmd_CreateDebug(ovrHmd_DK2, &d_hmd);
	}
	//If even a virtual HMD cannot be created, there's probably 
	//something wrong with the Oculus runtime and the program will stop
	if (!OVR_SUCCESS(result))
	{
		std::cerr << "Oculus Rift not detected. You might want to install it\n";
		exit(EXIT_FAILURE);
	}


	//Since the Rift's display is based on stereo view, we have to render the scene twice,
	//once for each eye. This is why we will often make a 2-iterations loop, one iteration for each eye
	//Here, we create two textures and two depth buffers to store the rendering for both eyes
	for (int i = 0; i<2; i++)
	{
		ovrSizei idealTextureSize = ovrHmd_GetFovTextureSize(d_hmd, (ovrEyeType)i, d_hmd->DefaultEyeFov[i], 1);
		d_eyeRenderTexture[i] = new TextureBuffer(d_hmd, true, true, idealTextureSize, 1, NULL, 1);
		d_eyeDepthBuffer[i] = new DepthBuffer(d_eyeRenderTexture[i]->GetSize());
	}

	//Creates the mirror texture and an FBO used to mirror the Rift's display onto the regular screen
	ovrSizei windowSize = { d_hmd->Resolution.w / 2, d_hmd->Resolution.h / 2 };
	ovrHmd_CreateMirrorTextureGL(d_hmd, GL_RGBA, windowSize.w, windowSize.h, (ovrTexture**)&d_mirrorTexture);

	//Generates and binds the FrameBuffer Object used to render the mirror texture
	glGenFramebuffers(1, &d_mirrorFBO);
	glBindFramebuffer(GL_READ_FRAMEBUFFER, d_mirrorFBO);
	glFramebufferTexture2D(GL_READ_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, d_mirrorTexture->OGL.TexId, 0);
	glFramebufferRenderbuffer(GL_READ_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, 0);
	glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);

	//sets up the rendering information of both eyes based on the HMD's characteristics and configuration
	d_EyeRenderDesc[0] = ovrHmd_GetRenderDesc(d_hmd, ovrEye_Left, d_hmd->DefaultEyeFov[0]);
	d_EyeRenderDesc[1] = ovrHmd_GetRenderDesc(d_hmd, ovrEye_Right, d_hmd->DefaultEyeFov[1]);

	ovrHmd_SetEnabledCaps(d_hmd, ovrHmdCap_LowPersistence | ovrHmdCap_DynamicPrediction);

	//Starts the sensor's tracking
	ovrHmd_ConfigureTracking(d_hmd, ovrTrackingCap_Orientation | ovrTrackingCap_MagYawCorrection |
		ovrTrackingCap_Position, 0);

	//The VSync must be turned off in order for the compositor to work properly
	//Since this is related to the system on which the program is running, the function to use differs
	//between Windows and OSX. ubuntu does not fully work on Ubuntu so there is no need to worry about that yet
	wglSwapIntervalEXT(0); // WARNING !! THIS ONLY WORKS WITH WINDOWS 
	//glxSwapIntervalEXT(0); //this might be the right call for OS X...

	//now that everything is set up, we can start rendering
	d_isVisible = true;
}


void RiftHandler::DisplayOnRift()
{
	//Distance between the center of the HMD and the eyes
	ovrVector3f ViewOffset[2] = { d_EyeRenderDesc[0].HmdToEyeViewOffset, d_EyeRenderDesc[1].HmdToEyeViewOffset };
	//Pose of the eyes
	ovrPosef EyeRenderPose[2];
	//Timing used for the rendering. 
	//    See documentation for more details about the use of time in the Rift's rendering process
	ovrFrameTiming frameTiming = ovrHmd_GetFrameTiming(d_hmd, 0);
	//Pose of the HMD
	ovrTrackingState hmdState = ovrHmd_GetTrackingState(d_hmd, frameTiming.DisplayMidpointSeconds);
	//offset eye poses based on headPose --> WARNING
	ovr_CalcEyePoses(hmdState.HeadPose.ThePose, ViewOffset, EyeRenderPose);

	if (d_isVisible)
	{
		for (int eye = 0; eye<2; eye++)
		{
			// Increment to use next texture, just before writing
			d_eyeRenderTexture[eye]->TextureSet->CurrentIndex = (d_eyeRenderTexture[eye]->TextureSet->CurrentIndex + 1) % d_eyeRenderTexture[eye]->TextureSet->TextureCount;

			// Switch to eye render target
			d_eyeRenderTexture[eye]->SetAndClearRenderSurface(d_eyeDepthBuffer[eye]);

			OVR::Matrix4f rotationMatrix = OVR::Matrix4f(EyeRenderPose[eye].Orientation);
			OVR::Vector3f cam_up = rotationMatrix.Transform(OVR::Vector3f(0, 1, 0));
			OVR::Vector3f cam_look = rotationMatrix.Transform(OVR::Vector3f(0, 0, -1));
			OVR::Vector3f cam_pos = OVR::Vector3f(0.0, 0.0, 0.0);

			OVR::Matrix4f view = OVR::Matrix4f::LookAtRH(cam_pos, cam_look, cam_up);
			OVR::Matrix4f proj = ovrMatrix4f_Projection(d_hmd->DefaultEyeFov[eye], 0.001f, 1000.0f, ovrProjection_RightHanded);

			// Render world
			d_viewProjMatrix = proj*view;

			d_displayFunction();//calls the display function

			// Avoids an error when calling SetAndClearRenderSurface during next iteration.
			// Without this, during the next while loop iteration SetAndClearRenderSurface
			// would bind a framebuffer with an invalid COLOR_ATTACHMENT0 because the texture ID
			// associated with COLOR_ATTACHMENT0 had been unlocked by calling wglDXUnlockObjectsNV.
			d_eyeRenderTexture[eye]->UnsetRenderSurface();
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
		ld.ColorTexture[eye] = d_eyeRenderTexture[eye]->TextureSet;
		ld.Viewport[eye] = OVR::Recti(d_eyeRenderTexture[eye]->GetSize());
		ld.Fov[eye] = d_hmd->DefaultEyeFov[eye];
		ld.RenderPose[eye] = EyeRenderPose[eye];
	}

	ovrLayerHeader* layers = &ld.Header;
	ovrResult result = ovrHmd_SubmitFrame(d_hmd, 0, &viewScaleDesc, &layers, 1);
	d_isVisible = OVR_SUCCESS(result);

	// Blit mirror texture to back buffer
	glBindFramebuffer(GL_READ_FRAMEBUFFER, d_mirrorFBO);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	GLint w = d_mirrorTexture->OGL.Header.TextureSize.w;
	GLint h = d_mirrorTexture->OGL.Header.TextureSize.h;
	glBlitFramebuffer(0, h, w, 0,
		0, 0, w, h,
		GL_COLOR_BUFFER_BIT, GL_NEAREST);
	glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);

}

void RiftHandler::CleanUp()
{
	ovrHmd_Destroy(d_hmd);
	ovr_Shutdown();
}