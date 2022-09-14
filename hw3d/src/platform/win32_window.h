#ifndef WIN32_WINDOW_H
#define WIN32_WINDOW_H

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <string>

struct win32_wnd_context_t
{
	win32_wnd_context_t(void) {
		window = NULL;
		hInstance = NULL;
		width = 0;
		height = 0;
		flags = 0;
		title = "";
		className = "";
		wTitle = L"";
		wClassName = L"";
	}
	~win32_wnd_context_t(void) {

		if (window != NULL)
		{
			UnregisterClass(wClassName.c_str(), hInstance);
			DestroyWindow(window);
			window = NULL;
		}

	}
	HWND window;
	HINSTANCE hInstance;
	std::string title;
	std::string className;
	std::wstring wTitle;
	std::wstring wClassName;
	int width, height, flags;
} typedef W32WC;

bool win32_window_context_make(W32WC* pWin32WindowContext,
	HINSTANCE instance,
	std::string title,
	std::string className,
	const int width, const int height, const int flags);

#include "../defines.h"

force_inline bool win32_window_proc_msg(W32WC& refWin32WindowContext) {
	MSG msg = { 0 };
	ZeroMemory(&msg, sizeof(MSG));

	while (PeekMessage(&msg, refWin32WindowContext.window, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	if (msg.message == WM_NULL)
	{
		if (!IsWindow(refWin32WindowContext.window)) {
			refWin32WindowContext.window = NULL;
			UnregisterClass(refWin32WindowContext.wClassName.c_str(), refWin32WindowContext.hInstance);
			return(false);
		}
	}

	return(true);
}


#endif // !WIN32_WINDOW_H

