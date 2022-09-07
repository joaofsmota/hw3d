#ifndef D3D_RENDERER_H
#define D3D_RENDERER_H

#include <d3d11.h>
#include <wrl/client.h>
#pragma comment(lib, "d3d11")
#pragma comment(lib, "DirectXTK")
#pragma comment(lib, "dxgi")

struct D3D11Context_t
{
	D3D11Context_t(void) {
	}
	~D3D11Context_t(void) {
	}

	Microsoft::WRL::ComPtr<ID3D11Device> device;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext;
	Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> renderTargetView;

} typedef D3D11DC_t;


bool d3d11_context_make(HWND hwnd, int width, int height);

#endif // !D3D_RENDERER_H
