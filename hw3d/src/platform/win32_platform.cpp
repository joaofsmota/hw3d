/*
    Windows app entry point.
*/

#include "win32_window.h" // defines WIN32_LEAN_AND_MEAN + includes <Windows.h>.

#include "../renderer/d3d11_renderer.h"

int WINAPI wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR pCmdLine, _In_ int nCmdShow)
{
    (void)hPrevInstance; 
    (void)pCmdLine; 
    (void)nCmdShow; 

    W32WC_t win32WindowContext = {};
    if (!win32_window_context_make(&win32WindowContext, hInstance, "Title", "WindowClass", 1280, 820, 0)) {
        return(-1);
    }

    D3D11DC_t d3d11Context = {};
    if (!d3d11_context_make(win32WindowContext.window, win32WindowContext.width, win32WindowContext.height)){
        return(-1);
    }

    for (; win32_window_proc_msg(win32WindowContext) != false;)
    {
        Sleep(200);
    }

    return(0);
}

