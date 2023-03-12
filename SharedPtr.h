#pragma once
#include "Jade.h"

namespace Jade
{
	template<class T>
	class SharedPtr
	{
	public:
		SharedPtr() : Pointer(nullptr), RefCounter(nullptr) {}
		explicit SharedPtr(T* P) : Pointer(P), RefCounter(new int32(1)) {}
		SharedPtr(const SharedPtr& Other) : Pointer(Other.Pointer), RefCounter(Other.RefCounter)
		{
			IncrementRefCounter();
		}

		~SharedPtr()
		{
			RefCounterCheck();
		}

		SharedPtr& operator=(const SharedPtr& Other)
		{
			if (this != &Other)
			{
				RefCounterCheck();
			}

			Pointer = Other.Pointer;
			RefCounter = Other.RefCounter;
			
			IncrementRefCounter();
			return *this;
		}

		T* operator->() const { return Pointer; }
		T& operator*() const { return *Pointer; }
		operator bool() const { return Pointer != nullptr; }

	private:
		void RefCounterCheck()
		{
			if (RefCounter)
			{
				(*RefCounter)--;
				if (*RefCounter == 0)
				{
					SAFE_DELETE(Pointer);
					SAFE_DELETE(RefCounter);
				}
			}
		}

		void IncrementRefCounter()
		{
			if (RefCounter)
			{
				(*RefCounter)++;
			}
		}

	private:
		T* Pointer;
		int32* RefCounter;
	};
}
