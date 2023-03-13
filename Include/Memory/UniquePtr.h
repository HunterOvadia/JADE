#pragma once
namespace Jade
{
	template<typename T>
	class UniquePtr
	{
	public:
		explicit UniquePtr(T* Pointer = nullptr) : InternalPointer(Pointer) {}
		~UniquePtr()
		{
			delete InternalPointer;
			InternalPointer = nullptr;
		}

		UniquePtr(const UniquePtr<T>&) = delete;
		UniquePtr<T>& operator=(const UniquePtr<T>&) = delete;
		UniquePtr(UniquePtr<T>&& Other) noexcept
		{
			InternalPointer = Other.InternalPointer;
			Other.InternalPointer = nullptr;
		}

		UniquePtr<T>& operator=(UniquePtr<T>&& Other) noexcept
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

