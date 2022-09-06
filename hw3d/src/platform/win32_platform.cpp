#pragma comment(lib, "d3d11")
#pragma comment(lib, "DirectXTK")

/*
    Windows app entry point.
*/

#include "../core/engine.h"
using namespace engine::win32; // defines WIN32_LEAN_AND_MEAN + includes <Windows.h>. 

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
    };

    for (; win32_window_proc_msg(win32WindowContext) != false;)
    {
        Sleep(50);
    }

    return(0);
}

