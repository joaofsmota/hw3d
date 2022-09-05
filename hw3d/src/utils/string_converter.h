#ifndef STRING_CONVERTER_H
#define STRING_CONVERTER_H

#include <string>
#include "../defines.h"

namespace utils {
	/*
		DX11 API expects wide strings.
	*/
	IFORCE_INLINE std::wstring string_to_wstring(std::string str) {
		return(std::wstring(str.begin(), str.end()));
	}
}

#endif // !STRING_CONVERTER_H
