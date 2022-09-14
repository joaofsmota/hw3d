/*
    Windows app entry point.
*/
#include "../core/engine.h"

#include "win32_window.h" // defines WIN32_LEAN_AND_MEAN + includes <Windows.h>.

#include "../renderer/d3d11/d3d11_renderer.h"
#include "../renderer/d3d11/shader.h"

struct engine_t {
    engine_t(void) {
        windowContext = {};
        gfxContext = {};
    }
    ~engine_t(void) {}
    W32WC windowContext;
    D3D11GC gfxContext;
};

static engine_t globalEngine = {}; 

int WINAPI wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR pCmdLine, _In_ int nCmdShow)
{
    (void)hPrevInstance; 
    (void)pCmdLine; 
    (void)nCmdShow;

    {
        if (!win32_window_context_make(&globalEngine.windowContext, hInstance, "Title", "WindowClass", 1280, 820, 0))
            return(-1);


        if (!d3d11_context_make(&globalEngine.gfxContext,
            globalEngine.windowContext.window,
            globalEngine.windowContext.width,
            globalEngine.windowContext.height)) return(-1);

        if (!Pipeline::init_shader_stage(&globalEngine.gfxContext)) return(-1);


        shader_t<D3D11SHADER::VertexShader> v = {};
        CmdShader<D3D11SHADER::VertexShader>::init(&v, globalEngine.gfxContext.device, L"");

        for (; win32_window_proc_msg(globalEngine.windowContext) != false;)
        {

            d3d11_render_frame(&globalEngine.gfxContext);

            Sleep(200);
        }
    }

    return(0);
}

