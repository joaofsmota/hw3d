#ifndef MEM_ZONE_H
#define MEM_ZONE_H

#include "../../defines.h"
#include "../../types.h"

/*
	Arena/Zone-Based Allocation; Derived from: https://www.pbr-book.org/3ed-2018/Utilities/Memory_Management#fragment-MemoryDeclarations-3
*/

namespace memory {

	// 'constexpr' functions will be implicitly inlined => no need for IFORCE_INLINE
	constexpr u64 Kilobytes(const u64 value) {
		return((u64)((value) * 1024)); // will further u64 casting be necessary ?
	}
	constexpr u64 Megabytes(const u64 value) {
		return((u64)(Kilobytes(value) * 1024));
	}
	constexpr u64 Gigabytes(const u64 value) {
		return((u64)(Megabytes(value) * 1024));
	}

	struct Mem_Zone_t
	{
		Mem_Zone_t(void) {

		}
		~Mem_Zone_t(void) {

		}
	private:

	};

}

#endif // !MEM_ARENA_H
