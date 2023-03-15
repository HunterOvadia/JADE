#pragma once
#include "Jade.h"

namespace Jade
{
	template<typename T, uint64 Count>
	class Vector
	{
	public:
		template<typename... TArgs>
		explicit Vector(TArgs... Args) : Elements{Args...} {}

		T& operator[](int Index)
		{
			return Elements[Index];
		}

		const T& operator[](int Index) const
		{
			return Elements[Index];
		}

		bool operator!=(const Vector& Lhs)
		{
			return Elements != Lhs.Elements;
		}

	protected:
		T Elements[Count];
	};

	template<typename T>
	class Vector2 : public Vector<T, 2>
	{
		using TVector = Vector<T, 2>;

	public:
		Vector2() : TVector(static_cast<T>(0), static_cast<T>(0)) {}
		Vector2(T X, T Y) : TVector(X, Y) {}
		T& X() { return this->Elements[0]; }
		T& Y() { return this->Elements[1]; }
	};

	template<typename T>
	class Vector3 : public Vector<T, 3>
	{
		using TVector = Vector<T, 3>;

	public:
		Vector3() : TVector(static_cast<T>(0), static_cast<T>(0), static_cast<T>(0)) {}
		Vector3(T X, T Y, T Z) : TVector(X, Y, Z) {}
		T& X() { return this->Elements[0]; }
		T& Y() { return this->Elements[1]; }
		T& Z() { return this->Elements[2]; }
	};

	template<typename T>
	class Vector4 : public Vector<T, 4>
	{
		using TVector = Vector<T, 4>;

	public:
		Vector4() : TVector(static_cast<T>(0), static_cast<T>(0), static_cast<T>(0), static_cast<T>(0)) {}
		Vector4(T X, T Y, T Z, T W) : TVector(X, Y, Z, W) {}
		T& X() { return this->Elements[0]; }
		T& Y() { return this->Elements[1]; }
		T& Z() { return this->Elements[2]; }
		T& W() { return this->Elements[3]; }
	};
}
