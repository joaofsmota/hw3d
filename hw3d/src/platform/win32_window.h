#ifndef WIN32_WINDOW_H
#define WIN32_WINDOW_H

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <string>

struct Win32_Window_Context_t
{
	Win32_Window_Context_t(void) {
		window_ = NULL;
		hInstance_ = NULL;
		W_ = 0;
		H_ = 0;
		flags_ = 0;
		title_ = "";
		className_ = "";
		wTitle_ = L"";
		wClassName_ = L"";
	}
	~Win32_Window_Context_t(void) {

		if (window_ != NULL)
		{
			UnregisterClass(wClassName_.c_str(), hInstance_);
			DestroyWindow(window_);
			window_ = NULL;
		}

	}
	HWND window_;
	HINSTANCE hInstance_;
	std::string title_;
	std::string className_;
	std::wstring wTitle_;
	std::wstring wClassName_;
	int W_, H_, flags_;
} typedef W32WC_t;

bool win32_window_context_make(W32WC_t* pContext,
	HINSTANCE instance,
	std::string title,
	std::string className,
	const int width, const int height, const int flags);

#include "../defines.h"

IFORCE_INLINE bool win32_window_proc_msg(W32WC_t& context) {
	MSG msg = { 0 };
	ZeroMemory(&msg, sizeof(MSG));

	if (PeekMessage(&msg, context.window_, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	if (msg.message == WM_NULL)
	{
		if (!IsWindow(context.window_)) {
			context.window_ = NULL;
			UnregisterClass(context.wClassName_.c_str(), context.hInstance_);
			return(false);
		}
	}

	return(true);
}


#endif // !WIN32_WINDOW_H

