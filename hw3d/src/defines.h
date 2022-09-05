#ifndef DEFINES_H
#define DEFINES_H

#define IDEBUG

#if defined (_WIN32)
	#define IWIN32_DEBUG_BUILD
	/*
	MSVC is preferable for compilation on Windows.
	MSVC specific.
	*/
	#define IFORCE_INLINE __forceinline
#elif defined (__linux)
	#define PLATFORM "Linux"
#endif

#endif // !DEFINES_H

