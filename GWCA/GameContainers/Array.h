#pragma once

#include <Windows.h>

namespace GW {

	// class Array
	// generic game container seen throughout the games memory.
	// reccomended to only use references to maintain up-to-date information ( Array<T>& )

	template <typename T>
	class Array {
	public:
		enum class Exception {
			kOutOfBounds,   // index is beyond the current size of the array
			kInvalidArray   // array pointer is null
		};

		typedef       T* iterator;
		typedef const T* const_iterator;

		iterator       begin()       { return Buff; }
		const_iterator begin() const { return Buff; }
		iterator       end()         { return Buff + Size; }
		const_iterator end()   const { return Buff + Size; }

		T& index(DWORD index) {
			if (!valid())
				throw Exception::kInvalidArray;
			if (index >= size() || index < 0)
				throw Exception::kOutOfBounds;
			return Buff[index];
		}

		T& operator[](DWORD index) {
		#ifdef NDEBUG
			return Buff[index];
		#else
			return this->index(index);
		#endif
		}

		bool valid() { return Buff != nullptr; }

		DWORD size()     const { return Size; }
		DWORD capacity() const { return Capacity; }

	protected:
		T*	  Buff;		// + 0x0000
		DWORD Capacity;	// + 0x0004
		DWORD Size;		// + 0x0008
		DWORD Unk0;		// + 0x000C
	}; // Size: 0x0010
}
