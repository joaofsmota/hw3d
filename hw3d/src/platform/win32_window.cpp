#include "win32_window.h"

#include "win32_debug.h"
#include "../core/debug.h"
#include "../utils/string_converter.h"

LRESULT win32_window_proc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

bool win32_window_context_make(W32WC_t* pContext,
	HINSTANCE instance,
	std::string title,
	std::string className,
	const int width, const int height, const int flags) {

	if (pContext->window != NULL) return(false);

	pContext->hInstance = instance;
	pContext->width = width;
	pContext->height = height;
	pContext->flags = flags;
	pContext->title = title;
	pContext->className = className;
	pContext->wTitle = utils::string_to_wstring(title);
	pContext->wClassName = utils::string_to_wstring(className);

	WNDCLASSEX wc = { };
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = win32_window_proc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = instance;
	wc.hIcon = NULL;
	wc.hIconSm = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = NULL;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = pContext->wClassName.c_str();

	AssertRaw(RegisterClassEx(&wc) != 0)

		pContext->window = CreateWindowEx(
			WS_EX_APPWINDOW,
			wc.lpszClassName,
			pContext->wTitle.c_str(),
			WS_VISIBLE | (WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME), // <- flags
			CW_USEDEFAULT, CW_USEDEFAULT,
			width, height,
			NULL, NULL,
			instance,
			NULL);

	if (pContext->window == NULL)
	{
		win32_debug::Log(GetLastError(), "CreateWindowEx Failed for window: " + title);

		return(false);
	}
	else
	{
		AssertRaw(ShowWindow(pContext->window, SW_SHOW) != 0)
			AssertRaw(SetForegroundWindow(pContext->window) != 0)
			AssertRaw(UpdateWindow(pContext->window) != 0)
			SetFocus(pContext->window);

		return(true);
	}
}

LRESULT win32_window_proc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg)
	{
	case WM_CLOSE: {
		DestroyWindow(hwnd);
	}break;
	case WM_MOUSEMOVE: {

	}break; 
	case WM_SIZE: {
	}break;
	case WM_DESTROY: {
		PostQuitMessage(0);
	}break;
	default: return(DefWindowProcA(hwnd, msg, wParam, lParam));
	}
	return(0);
}