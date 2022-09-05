#pragma comment(lib, "d3d11")
#pragma comment(lib, "DirectXTK")

#include "win32_window.h" // defines WIN32_LEAN_AND_MEAN + includes <Windows.h>. 
#include "../core/debug.h"

int WINAPI wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR pCmdLine, _In_ int nCmdShow)
{
    (void)hPrevInstance; 
    (void)pCmdLine; 
    (void)nCmdShow; 

    W32WC_t context = {};
    if (!win32_window_context_make(&context, hInstance, "Title", "WindowClass", 1280, 820, 0)) {
        return(-1);
    };

    for (; win32_window_proc_msg(context) != false;)
    {
        Sleep(50);
    }

    return(0);
}

