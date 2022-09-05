#ifndef DEBUG_H
#define DEBUG_H

#include "../defines.h"
#include "../types.h"

/*
	Raw/abrupt assertions.
*/
#ifdef IDEBUG
	#define AssertRaw(expression) if(!(expression)) { *(s32 *)0 = 0; }
#elif IRELEASE
	#define AssertRaw(expression)
#endif // IDEBUG

#endif // !DEBUG_H

