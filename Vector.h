#pragma once
#include <type_traits>
#include <tuple>

namespace Jade
{
	template<typename T, uint64 Count>
	class Vector
	{
	public:
		template<typename... TArgs>
		Vector(TArgs... Args) : Elements{Args...} {}

		T& operator[](int Index)
		{
			return Elements[Index];
		}

		const T& operator[](int Index) const
		{
			return Elements[Index];
		}

	protected:
		T Elements[Count];
	};

	template<typename T>
	class Vector2 : public Vector<T, 2>
	{
		using TVector = Vector<T, 2>;

	public:
		Vector2() : TVector((T)0, (T)0) {}
		Vector2(T X, T Y) : TVector(X, Y) {}
		T& X() { return this->Elements[0]; }
		T& Y() { return this->Elements[1]; }
	};

	template<typename T>
	class Vector3 : public Vector<T, 3>
	{
		using TVector = Vector<T, 3>;

	public:
		Vector3() : TVector((T)0, (T)0, (T)0) {}
		Vector3(T X, T Y, T Z) : TVector(X, Y, Z) {}
		T X() const { return this->Elements[0]; }
		T Y() const { return this->Elements[1]; }
		T Z() const { return this->Elements[2]; }
	};

	template<typename T>
	class Vector4 : public Vector<T, 4>
	{
		using TVector = Vector<T, 4>;

	public:
		Vector4() : TVector((T)0, (T)0, (T)0, (T)0) {}
		Vector4(T X, T Y, T Z, T W) : TVector(X, Y, Z, W) {}
		T X() const { return this->Elements[0]; }
		T Y() const { return this->Elements[1]; }
		T Z() const { return this->Elements[2]; }
		T W() const { return this->Elements[3]; }
	};
}
