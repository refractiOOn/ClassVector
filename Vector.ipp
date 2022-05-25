#pragma once

#include "Vector.hpp"

template<typename T> Vector<T>::Vector(const size_t pSize) :
	mSize(pSize),
	mCapacity(pSize),
	mData(std::make_unique<T[]>(pSize))
{
	for (size_t i = 0; i < mSize; ++i)
	{
		mData[i] = {};
	}
}

template<typename T> Vector<T>::Vector(const size_t pSize, T pValue) :
	mSize(pSize),
	mCapacity(pSize),
	mData(std::make_unique<T[]>(pSize))
{
	for (size_t i = 0; i < mSize; ++i)
	{
		mData[i] = pValue;
	}
}

template<typename T> Vector<T>::Vector(const std::initializer_list<T>& pInitList) :
	mSize(pInitList.size()),
	mCapacity(pInitList.size()),
	mData(std::make_unique<T[]>(pInitList.size()))
{
	auto it = pInitList.begin();
	for (size_t i = 0; i < mSize; ++i)
	{
		mData[i] = *it;
		++it;
	}
}

template<typename T> Vector<T>::Vector(const Vector<T>& pOther) :
	mCapacity(pOther.mCapacity),
	mSize(pOther.mSize),
	mData(std::make_unique<T[]>(pOther.mCapacity))
{
	for (size_t i = 0; i < mCapacity; ++i)
	{
		mData[i] = pOther.mData[i];
	}
}

template<typename T> Vector<T>::Vector(Vector<T>&& pOther) :
	mCapacity(pOther.mCapacity),
	mSize(pOther.mSize),
	mData(pOther.mData.release())
{
	pOther.mSize = 0, pOther.mCapacity = 0;
}

template<typename T> Vector<T>& Vector<T>::operator=(const std::initializer_list<T>& pInitList)
{
	mSize = pInitList.size();
	mCapacity = mSize * 1.5;

	mData.reset();
	mData = std::make_unique<T[]>(mCapacity);

	auto it = pInitList.begin();
	for (size_t i = 0; i < mSize; ++i)
	{
		mData[i] = *it;
		++it;
	}

	return *this;
}

template<typename T> Vector<T>& Vector<T>::operator=(const Vector<T>& pOther)
{
	if (this == &pOther) return *this;

	mSize = pOther.mSize, mCapacity = pOther.mCapacity;

	mData.reset();
	mData = std::make_unique<T[]>(mCapacity);
	for (size_t i = 0; i < mSize; ++i)
	{
		mData[i] = pOther.mData[i];
	}

	return *this;
}

template<typename T> Vector<T>& Vector<T>::operator=(Vector<T>&& pOther)
{
	mSize = pOther.mSize, mCapacity = pOther.mCapacity;
	pOther.mSize = 0, pOther.mCapacity = 0;

	mData = std::move(pOther.mData());

	return *this;
}

template<typename T> Vector<T>::~Vector() noexcept
{
	mSize = 0, mCapacity = 0;
	mData.reset();
}

template<typename T> void Vector<T>::PushBack(T pValue)
{
	if (mSize == mCapacity)
	{
		Reserve(mCapacity * 1.5);
	}

	mData[mSize] = pValue;
	++mSize;
}

template<typename T> void Vector<T>::PopBack() noexcept
{
	if (!mSize) return;

	mData[mSize - 1] = {};
	--mSize;
}

template<typename T> void Vector<T>::Swap(Vector<T>& pOther) noexcept
{
	std::unique_ptr<T[]> buffer = std::move(mData);
	mData = std::move(pOther.mData);
	pOther.mData = std::move(buffer);

	std::swap(mCapacity, pOther.mCapacity);
	std::swap(mSize, pOther.mSize);
}

template<typename T> void Vector<T>::Clear() noexcept
{
	mData.reset();
	mSize = 0, mCapacity = 0;
}

template<typename T> size_t Vector<T>::Size() const noexcept
{
	return mSize;
}

template<typename T> size_t Vector<T>::Capacity() const noexcept
{
	return mCapacity;
}

template<typename T> bool Vector<T>::Empty() const noexcept
{
	return mSize == 0;
}

template<typename T> void Vector<T>::Resize(const size_t pSize)
{
	if (pSize > mCapacity)
	{
		Reserve(pSize);
	}

	for (size_t i = mSize; i < pSize; ++i)
	{
		mData[i] = {};
	}

	mSize = pSize;
}

template<typename T> void Vector<T>::Reserve(const size_t pCapacity)
{
	if (pCapacity <= mCapacity) return;

	std::unique_ptr<T[]> tmp(mData.release());
	mData = std::make_unique<T[]>(pCapacity);
	for (size_t i = 0; i < mSize; ++i)
	{
		mData[i] = tmp[i];
	}

	mCapacity = pCapacity;
}

template<typename T> void Vector<T>::ShrinkToFit() noexcept
{
	Reserve(mSize);
}

template<typename T> T& Vector<T>::At(const size_t pIndex)
{
	return mData[pIndex];
}

template<typename T> T& Vector<T>::Front()
{
	return mData[0];
}

template<typename T> T& Vector<T>::Back()
{
	return mData[mSize - 1];
}

template<typename T> T* Vector<T>::Data()
{
	return mData.get();
}

template<typename T> T& Vector<T>::operator[](size_t pIndex)
{
	return mData[pIndex];
}