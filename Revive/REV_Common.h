#pragma once

#include "OVR_CAPI.h"
#include "openvr.h"
#include <vector>

// Common structures

#define REV_SWAPCHAIN_LENGTH 2

struct ovrTextureSwapChainData
{
	ovrTextureSwapChainDesc Desc;
	vr::EGraphicsAPIConvention ApiType;
	int Length, CurrentIndex;
	vr::Texture_t Textures[2];
	vr::Texture_t* Submitted;
	vr::VROverlayHandle_t Overlay;

	ovrTextureSwapChainData(vr::EGraphicsAPIConvention api, ovrTextureSwapChainDesc desc);
	~ovrTextureSwapChainData();
};

struct ovrMirrorTextureData
{
	ovrMirrorTextureDesc Desc;
	vr::EGraphicsAPIConvention ApiType;
	vr::Texture_t Texture;
	void* Views[ovrEye_Count];
	void* Target;
	void* Shader;

	ovrMirrorTextureData(vr::EGraphicsAPIConvention api, ovrMirrorTextureDesc desc);
	~ovrMirrorTextureData();
};

struct ovrHmdStruct
{
	// Session status
	bool ShouldQuit;
	bool IsVisible;
	char StringBuffer[vr::k_unMaxPropertyStringSize];
	long long FrameIndex;

	// Controller states
	bool ThumbStick[ovrHand_Count];
	bool MenuWasPressed[ovrHand_Count];
	float ThumbStickRange;

	// Device poses
	vr::TrackedDevicePose_t Poses[vr::k_unMaxTrackedDeviceCount];
	vr::TrackedDevicePose_t GamePoses[vr::k_unMaxTrackedDeviceCount];

	// Overlays
	unsigned int OverlayCount;
	std::vector<vr::VROverlayHandle_t> ActiveOverlays;

	// Mirror texture
	ovrMirrorTexture MirrorTexture;

	ovrHmdStruct();
	~ovrHmdStruct();
};

// Common functions

unsigned int rev_TrackedDevicePoseToOVRStatusFlags(vr::TrackedDevicePose_t pose);
vr::VRTextureBounds_t rev_ViewportToTextureBounds(ovrRecti viewport, ovrTextureSwapChain swapChain, unsigned int flags);
vr::VROverlayHandle_t rev_CreateOverlay(ovrSession session);

// Graphics functions

void rev_DestroyTextureSwapChainDX(ovrTextureSwapChain chain);
void rev_DestroyTextureSwapChainGL(ovrTextureSwapChain chain);
void rev_DestroyMirrorTextureDX(ovrMirrorTexture mirrorTexture);
void rev_DestroyMirrorTextureGL(ovrMirrorTexture mirrorTexture);
void rev_RenderMirrorTextureDX(ovrMirrorTexture mirrorTexture);
void rev_RenderMirrorTextureGL(ovrMirrorTexture mirrorTexture);
