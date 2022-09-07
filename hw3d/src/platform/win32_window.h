#ifndef WIN32_WINDOW_H
#define WIN32_WINDOW_H

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <string>

struct W32WindowContext_t
{
	W32WindowContext_t(void) {
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
	~W32WindowContext_t(void) {

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
} typedef W32WC_t;

bool win32_window_context_make(W32WC_t* pContext,
	HINSTANCE instance,
	std::string title,
	std::string className,
	const int width, const int height, const int flags);

#include "../defines.h"

force_inline bool win32_window_proc_msg(W32WC_t& context) {
	MSG msg = { 0 };
	ZeroMemory(&msg, sizeof(MSG));

	if (PeekMessage(&msg, context.window, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	if (msg.message == WM_NULL)
	{
		if (!IsWindow(context.window)) {
			context.window = NULL;
			UnregisterClass(context.wClassName.c_str(), context.hInstance);
			return(false);
		}
	}

	return(true);
}


#endif // !WIN32_WINDOW_H

