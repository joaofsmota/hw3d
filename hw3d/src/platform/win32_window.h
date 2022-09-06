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


#endif // !WIN32_WINDOW_H

