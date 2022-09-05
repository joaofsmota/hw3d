#ifndef STRING_CONVERTER_H
#define STRING_CONVERTER_H

#include <string>

namespace utils {
	/*
		DX11 API expects wide strings.
	*/
	inline std::wstring string_to_wstring(std::string str) {
		return(std::wstring(str.begin(), str.end()));
	}
}

#endif // !STRING_CONVERTER_H
