#include "d3d11_renderer.h"

#include "../types.h"
#include "../platform/win32_debug.h"

struct Adapter_t
{
	Adapter_t(Microsoft::WRL::ComPtr<IDXGIAdapter> pAdapter) : pAdapter(pAdapter) {
		HRESULT hr{ pAdapter->GetDesc(&this->desc) };
		if (FAILED(hr))
			win32_debug::Log(hr, "Failed to Get Description for IDXGIAdapter.");
	}
	~Adapter_t(void) {}
	Microsoft::WRL::ComPtr<IDXGIAdapter> pAdapter;
	DXGI_ADAPTER_DESC desc; 
};

static std::vector<Adapter_t> globalAdapters = {};

static void getAdapters(std::vector<Adapter_t>& out) {

	if (out.size() > 0) return;

	Microsoft::WRL::ComPtr<IDXGIFactory> pFray = {}; 

	HRESULT hr{ CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(pFray.GetAddressOf())) };

	if (FAILED(hr))
	{
		win32_debug::Log(hr, "Failed to create IDXGIFactory for enumerating adapters.");
		return; 
	}

	Microsoft::WRL::ComPtr<IDXGIAdapter> pAdapter = {};
	UINT index{ 0 };
	while (SUCCEEDED(pFray->EnumAdapters(index, &pAdapter)))
	{
		out.push_back(Adapter_t(pAdapter));
		index += 1;
	}

}

bool d3d11_context_make(HWND hwnd, int width, int height)
{

	getAdapters(globalAdapters);

	return(true);
}
