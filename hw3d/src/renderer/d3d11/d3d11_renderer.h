#ifndef D3D11_RENDERER_H
#define D3D11_RENDERER_H

#include "../../types.h"
#include "../../platform/win32_debug.h"

#include <d3d11.h>
#include <wrl/client.h>
#pragma comment(lib, "d3d11")
#pragma comment(lib, "DirectXTK")
#pragma comment(lib, "dxgi")

struct d3d11_gfx_context_t
{
	d3d11_gfx_context_t(void) {

		device = nullptr;
		deviceContext = nullptr;
		swapChain = nullptr;
		renderTargetView = nullptr;

		inputLayout = nullptr;
		vertexShaderBuffer = nullptr;

	}
	~d3d11_gfx_context_t(void) {
	}

	Microsoft::WRL::ComPtr<ID3D11Device> device;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext;
	Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> renderTargetView;

	Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout;
	Microsoft::WRL::ComPtr<ID3D10Blob> vertexShaderBuffer;

} typedef D3D11GC;

bool d3d11_context_make(D3D11GC* pD3D11GraphicsContext, HWND hwnd, int width, int height);


force_inline void d3d11_render_frame(const D3D11GC* pD3D11GraphicsContext) {

	const f32 clearColor[4] = { 1.000f, 0.753f, 0.796f, 1.000f };
	pD3D11GraphicsContext->deviceContext->ClearRenderTargetView(pD3D11GraphicsContext->renderTargetView.Get(), clearColor);



	pD3D11GraphicsContext->swapChain->Present(1, NULL);
}

struct Pipeline {
	static bool init_shader_stage(D3D11GC* pD3D11GraphicsContext);
};

inline bool Pipeline::init_shader_stage(D3D11GC* pD3D11GraphicsContext)
{
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION",
			0,
			DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT,
			0, 0 /*0 offset (it's the first element)*/,
			D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA,
			0
		},
	};

	const UINT numElementsInLayout = ARRAYSIZE(layout);

	HRESULT hr = pD3D11GraphicsContext->device->CreateInputLayout(layout,
		numElementsInLayout,
		pD3D11GraphicsContext->vertexShaderBuffer->GetBufferPointer(),
		pD3D11GraphicsContext->vertexShaderBuffer->GetBufferSize(),
		pD3D11GraphicsContext->inputLayout.GetAddressOf()
	);

	if (FAILED(hr)) {
		win32_debug::Log(hr, "Failed to create Input Layout.");
		return(false);
	}

	return(true);
}

#endif // !D3D11_RENDERER_H
