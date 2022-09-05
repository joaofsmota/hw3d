#ifndef DEBUG_H
#define DEBUG_H

#include "../defines.h"

/*
	Raw/abrupt assertions.
*/
#ifdef IDEBUG
	#define AssertRaw(expression) if(!(expression)) { *(int *)0 = 0; }
#elif IRELEASE
	#define AssertRaw(expression)
#endif // IDEBUG

#endif // !DEBUG_H

