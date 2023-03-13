#pragma once
namespace Jade
{
	template<typename T>
	class Buffer
	{
	public:
		Buffer(T* Data, const uint64 InSize) : MemoryBlock(Data), Size(InSize) {}
		explicit Buffer(const uint64 InSize) : MemoryBlock(nullptr), Size(InSize)
		{
			MemoryBlock = new T[Size];
		}

		Buffer(const Buffer& Other)
		{
			Copy(Other.MemoryBlock, Other.Size);
		}

		~Buffer()
		{
			delete[] MemoryBlock;
		}

		void Copy(const T* Source, uint64 SourceSize)
		{
			if (Size != SourceSize)
			{
				delete[] MemoryBlock;
				MemoryBlock = new T[SourceSize];
				Size = SourceSize;
			}

			memcpy(MemoryBlock, Source, Size * sizeof(T));
		}

		Buffer& operator=(const Buffer& Other)
		{
			if (this != &Other)
			{
				Copy(Other.MemoryBlock, Other.Size);
			}

			return *this;
		}

		operator T*() const
		{
			return MemoryBlock;
		}

		T& operator[](uint64 Index)
		{
			return MemoryBlock[Index];
		}

		const T& operator[](uint64 Index) const
		{
			return MemoryBlock[Index];
		}

		T* Get() const
		{
			return &MemoryBlock[0];
		}

		uint64 GetSize() const
		{
			return Size;
		}

	private:
		T* MemoryBlock;
		uint64 Size;
	};
}
