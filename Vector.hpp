#pragma once

#include <memory>

template<typename T> class Vector
{
public:
	Vector() = default;
	Vector(const size_t pSize);
	Vector(const size_t pSize, const T pValue);
	Vector(const std::initializer_list<T>& pInitList);
	Vector(const Vector<T>& pOther);
	Vector(Vector<T>&& pOther);

	Vector<T>& operator=(const std::initializer_list<T>& pInitList);
	Vector<T>& operator=(const Vector<T>& pOther);
	Vector<T>& operator=(Vector<T>&& pOther);

	virtual ~Vector() noexcept;

public:
	void PushBack(T pValue);
	void PopBack() noexcept;
	void Swap(Vector<T>& pOther) noexcept;
	void Clear() noexcept;
	
	size_t Size() const noexcept;
	size_t Capacity() const noexcept;
	bool Empty() const noexcept;
	void Resize(const size_t pSize);
	void Reserve(const size_t pCapacity);
	void ShrinkToFit() noexcept;

	T& At(const size_t pIndex);
	T& Front();
	T& Back();
	T* Data();
	T& operator[](const size_t pIndex);

private:
	size_t mSize = 0;
	size_t mCapacity = 0;
	std::unique_ptr<T[]> mData = nullptr;
};

#include "Vector.ipp"