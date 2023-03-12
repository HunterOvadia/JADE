#pragma once
#include "Buffer.h"

namespace Jade
{
	class String
	{
	public:
		String() : Internal(nullptr, 0) {}
		String(const char* Input) : Internal(nullptr, 0)
		{
			int64 Size = strlen(Input) + 1;
			Internal.Copy(Input, Size);
		}
		~String() {}

		String& operator=(const String& Other)
		{
			if (this != &Other)
			{
				Internal = Other.Internal;
			}

			return *this;
		}

		String operator+(const String& Other) const
		{
			return *this;
		}

		uint64 GetSize() const
		{
			return Internal.GetSize();
		}

		const char* CString() const
		{
			return Internal.Get();
		}

	private:
		Buffer<char> Internal;
	};
}