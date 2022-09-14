#include "d3d11_renderer.h"

#include <vector>

struct adapter_t
{
	adapter_t(IDXGIAdapter* pAdapter) : pAdapter(pAdapter) {
		HRESULT hr{ pAdapter->GetDesc(&this->desc) };
		if (FAILED(hr))
			win32_debug::Log(hr, "Failed to Get Description for IDXGIAdapter.");
	}
	~adapter_t(void) {}
	IDXGIAdapter* pAdapter;
	DXGI_ADAPTER_DESC desc; 
};

static std::vector<adapter_t> globalAdapters = {};

static void getAdapters(std::vector<adapter_t>& out) {

	if (out.size() > 0) return;

	Microsoft::WRL::ComPtr<IDXGIFactory> pFray = {}; 

	HRESULT hr{ CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(pFray.GetAddressOf())) };

	if (FAILED(hr))
	{
		win32_debug::Log(hr, "Failed to create IDXGIFactory for enumerating adapters.");
		return; 
	}

	IDXGIAdapter* pAdapter = NULL;
	UINT index{ 0 };
	while (SUCCEEDED(pFray->EnumAdapters(index, &pAdapter)))
	{
		out.push_back(adapter_t(pAdapter));
		index += 1;
	}

}

bool d3d11_context_make(D3D11GC* pD3D11GraphicsContext, HWND hwnd, int width, int height)
{

	getAdapters(globalAdapters);

	if (globalAdapters.size() < 1) {
		win32_debug::Log("No DXGI Adapters found.");
		return(false);
	}

	DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
	{
		ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
		// BufferDesc
		{
			swapChainDesc.BufferDesc.Width = width;
			swapChainDesc.BufferDesc.Height = height;
			swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
			swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
			swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
			swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		}
		// SampleDesc, fields are set to default; TODO: change in the future.
		{
			swapChainDesc.SampleDesc.Count = 1;
			swapChainDesc.SampleDesc.Quality = 0;
		}
		// BufferUsage
		{
			swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		}
		// BufferCount
		{
			swapChainDesc.BufferCount = 1;
		}
		// Window
		{
			swapChainDesc.OutputWindow = hwnd;
			swapChainDesc.Windowed = TRUE;
		}
		// SwapEffect -> for now buffers will not be reused after presenting
		{
			swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		}
		// flags
		{
			swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
		}
	}

	HRESULT hr{ D3D11CreateDeviceAndSwapChain(globalAdapters[0].pAdapter,
											  D3D_DRIVER_TYPE_UNKNOWN,
											  NULL, // SW driver type.
											  NULL, // flags for runtime layers.
											  NULL, // feature levels Array.
											  0,    // # of feature levels in Array
											  D3D11_SDK_VERSION,
											  &swapChainDesc, // sc description.
											  pD3D11GraphicsContext->swapChain.GetAddressOf(),
											  pD3D11GraphicsContext->device.GetAddressOf(),
											  NULL, // supported feature level
											  pD3D11GraphicsContext->deviceContext.GetAddressOf()) 
	};

	if (FAILED(hr)) {
		win32_debug::Log(hr, "Failed to Create device or swapchain.");
		return(false);
	}

	Microsoft::WRL::ComPtr<ID3D11Texture2D> backBuffer = {};

	hr = pD3D11GraphicsContext->swapChain->GetBuffer(0,
		__uuidof(ID3D11Texture2D),
		reinterpret_cast<void**>(backBuffer.GetAddressOf()));

	if (FAILED(hr)) {
		win32_debug::Log(hr, "Failed to get BackBuffer.");
		return(false);
	}

	// create render target view
	hr = pD3D11GraphicsContext->device->CreateRenderTargetView(
		backBuffer.Get(),
		NULL, 
		pD3D11GraphicsContext->renderTargetView.GetAddressOf());


	if (FAILED(hr)) {
		win32_debug::Log(hr, "Failed to Create render target view.");
		return(false);
	}

	// set render target
	const UINT numRenderTargets = 1;
	pD3D11GraphicsContext->deviceContext->OMSetRenderTargets(numRenderTargets,
		pD3D11GraphicsContext->renderTargetView.GetAddressOf(),
		NULL); // currently no depth stencil view.

	return(true);
}
