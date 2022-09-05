#ifndef WIN32_DEBUG_H
#define WIN32_DEBUG_H

#include "../defines.h"

/*
	Win32 api dependent Log system.
*/
#ifdef IWIN32_BUILD_AND_DEBUG 
	#define WIN32_LEAN_AND_MEAN
	#include <Windows.h>
	#include <comdef.h>
	#include "../utils/string_converter.h" // includes <string>.
	namespace win32_debug {
		extern inline int Log(std::string message) {
			return(MessageBoxA(NULL, message.c_str(), "Info", MB_ICONINFORMATION));
		}
		extern inline int Log(const HRESULT hr, std::string message) {
			_com_error error(hr);
			std::wstring errorMessage{ L"Error: " + utils::string_to_wstring(message) + L"\n" + error.ErrorMessage() };
			return(MessageBoxW(NULL, errorMessage.c_str(), L"Error", MB_ICONERROR));
		}
	}
#endif

#endif // !WIN32_DEBUG_H

