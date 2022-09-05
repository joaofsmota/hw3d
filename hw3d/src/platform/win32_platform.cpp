#pragma comment(lib, "d3d11")
#pragma comment(lib, "DirectXTK")

#include "../core/engine.h" // defines WIN32_LEAN_AND_MEAN + includes <Windows.h>. 

/*
    Windows app entry point.
*/

int WINAPI wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR pCmdLine, _In_ int nCmdShow)
{
    (void)hPrevInstance; 
    (void)pCmdLine; 
    (void)nCmdShow; 

    CEngine::Win32WindowContext = {};
    if (!CEngine::win32_window_context_make(&CEngine::Win32WindowContext, hInstance, "Title", "WindowClass", 1280, 820, 0)) {
        return(-1);
    };

    for (; CEngine::win32_window_proc_msg(CEngine::Win32WindowContext) != false;)
    {
        Sleep(50);
    }

    return(0);
}

