#ifndef ENGINE_H
#define ENGINE_H

/*
	CEngine class borrows platform specific functionality. 
	Why? This class glues together all the functions needed to make a platform specific window context and run it on the main loop.
*/

#include "debug.h"

#include "../platform/win32_window.h"

#if !defined(internal)
	#define internal static
#endif

struct CEngine
{
	internal W32WC_t w32WCGlobal;
	internal bool win32_window_context_make(W32WC_t* pContext,
						HINSTANCE instance,
						std::string title,
						std::string className,
						const int width, const int height, const int flags);
	internal LRESULT win32_window_proc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	internal IFORCE_INLINE bool win32_window_proc_msg(W32WC_t& context) {
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

};

#endif // !ENGINE_H
