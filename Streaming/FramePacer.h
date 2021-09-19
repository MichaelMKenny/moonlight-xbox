#pragma once
#include "pch.h"
#include <queue>
#include <mutex>
struct Frame
{
	Microsoft::WRL::ComPtr<ID3D11Texture2D> decodeTexture;
	Microsoft::WRL::ComPtr <IDXGIKeyedMutex> decodeMutex;
	HANDLE handle;
	Microsoft::WRL::ComPtr <ID3D11Texture2D> renderTexure;
	Microsoft::WRL::ComPtr <IDXGIKeyedMutex> renderMutex;
	std::mutex *mutex;
	int frameNumber;
};

class FramePacer
{
public:
	void Setup(int width, int height);
	void FramePacer::SubmitFrame(Microsoft::WRL::ComPtr<ID3D11Texture2D> texture, int index, Microsoft::WRL::ComPtr<ID3D11DeviceContext> decodeContext);
	int queueSize = 16;
	int catchUpThreshold = 4;
	Microsoft::WRL::ComPtr<ID3D11Device1> renderingDevice, decodingDevice;
	void PrepareFrameForRendering();
	Microsoft::WRL::ComPtr<ID3D11Texture2D> GetCurrentRenderingFrame();
	void FramePacer::ReleaseTexture();
private:
	bool catchingUp = false;
	int decodeIndex = -1;
	int renderIndex = -1;
	int droppedFrames = 0;
	std::vector<Frame> frames;
};
