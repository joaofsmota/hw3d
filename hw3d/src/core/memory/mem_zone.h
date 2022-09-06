#ifndef MEM_ZONE_H
#define MEM_ZONE_H

#include "../../defines.h"
#include "../../types.h"

#include "../debug.h"

/*
	Arena/Zone-Based Allocation; Derived from: https://www.pbr-book.org/3ed-2018/Utilities/Memory_Management#fragment-MemoryDeclarations-3
	Why: To prevent "allocation fests"; Bound available memory.
*/

#include <stdint.h>
#include <list>

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
		Mem_Zone_t(size_t blockSize = 262144) : blockSize_(blockSize) {
			currentBlock_ = (uint8_t*)NULL;

		}
		~Mem_Zone_t(void) {

		}
	private:
		const size_t blockSize_;
		u64 currentBlockPos_ = 0, currentAllocSize_ = 0;
		uint8_t* currentBlock_;
		std::list<std::pair<size_t, uint8_t*>> usedBlocks_, availableBlocks_;
	};

}

#endif // !MEM_ZONE_H
