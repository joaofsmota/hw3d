#ifndef SHADER_H
#define SHADER_H

#include "../../platform/win32_debug.h"

#pragma comment(lib, "D3DCompiler.lib")
#include <d3d11.h>
#include <wrl/client.h>
#include <d3dcompiler.h>

namespace D3D11SHADER {
	typedef ID3D11VertexShader VertexShader;
	typedef ID3D11PixelShader PixelShader;
}

template<typename D3D11SHADER>
struct shader_t
{
	shader_t(void) {
		shader = nullptr;
		shaderBuffer = nullptr;
	}
	~shader_t(void) {}
	Microsoft::WRL::ComPtr<D3D11SHADER> shader;
	Microsoft::WRL::ComPtr<ID3D10Blob> shaderBuffer;
};

template<typename D3D11SHADER>
struct CmdShader
{
	static bool init(shader_t<D3D11SHADER>*,
		Microsoft::WRL::ComPtr<ID3D11Device>&,
		std::wstring);
	// Runtime. 
	static bool init(shader_t<D3D11SHADER>**,
		Microsoft::WRL::ComPtr<ID3D11Device>&,
		std::wstring);
};

template<typename D3D11SHADER>
inline bool CmdShader<D3D11SHADER>::init(shader_t<D3D11SHADER>* pShader, Microsoft::WRL::ComPtr<ID3D11Device>& refDevice, std::wstring pathToShaderFile)
{
	(void)pShader;
	(void)refDevice;
	(void)pathToShaderFile;

	return(true);
}

template<typename D3D11SHADER> // init shader at runtime.
inline bool CmdShader<D3D11SHADER>::init(shader_t<D3D11SHADER>** ppShader, Microsoft::WRL::ComPtr<ID3D11Device>& refDevice, std::wstring pathToShaderFile)
{

	return(true);
}


#endif