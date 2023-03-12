#pragma once
#include <utility>

namespace Jade
{
	template<typename T>
	class UniquePtr
	{
	public:
		UniquePtr(T* Pointer = nullptr) : InternalPointer(Pointer) {}
		~UniquePtr()
		{
			delete InternalPointer;
			InternalPointer = nullptr;
		}

		UniquePtr(const UniquePtr<T>&) = delete;
		UniquePtr<T>& operator=(const UniquePtr<T>&) = delete;
		UniquePtr(UniquePtr<T>&& Other)
		{
			InternalPointer = Other.InternalPointer;
			Other.InternalPointer = nullptr;
		}

		UniquePtr<T>& operator=(UniquePtr<T>&& Other)
		{
			if (this != &Other)
			{
				delete InternalPointer;
				InternalPointer = Other.InternalPointer;
				Other.InternalPointer = nullptr;
			}

			return *this;
		}

		T* operator->() const
		{
			return InternalPointer;
		}

		T& operator*() const
		{
			return *InternalPointer;
		}

	private:
		T* InternalPointer;
	};
}

