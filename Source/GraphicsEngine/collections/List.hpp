#pragma once
#include <cassert>
#include <vector>
//maybe a std::vector wrapper maybe not

template<typename T>
//growable contiguous memory
class List
{
public:
	void Add(const T& aItem);

	template<typename ...Args>
	T& Emplace(Args && ...aArgs);


	//Removes first instance of
	void Remove(const T& aItem);

	template<typename IndexType>
	void RemoveAt(IndexType aIndex);

	template<typename IndexType>
	void Reserve(IndexType aIndex);

	template<typename IndexType>
	void Resize(IndexType aIndex);

	size_t Size() const;
	bool IsEmpty() const;

	void Clear();

	T* Data() { return myData.data(); }
	const T* Data() const { return myData.data(); }

	T& operator[](size_t aIndex) { return myData[aIndex]; }
	const T& operator[](size_t aIndex) const { return myData[aIndex]; }
	//T& operator[](int aIndex) { return myData[aIndex]; }
	//const T& operator[](int aIndex) const { return myData[aIndex]; }


private:
	std::vector<T> myData;
};





template<typename T>
inline void List<T>::Add(const T& aItem)
{
	myData.push_back(aItem);
}


template<typename T>
template<typename ...Args>
inline T& List<T>::Emplace(Args && ...aArgs)
{
	return myData.emplace_back(std::forward<Args>(aArgs)...);;
}


template<typename T>
template<typename IndexType>
inline void List<T>::RemoveAt(IndexType aIndex)
{
	static_assert(std::is_arithmetic<IndexType>::value, "aIndex have to be numeric, List::RemoveAt");
	assert(aIndex >= 0 && static_cast<size_t>(aIndex) < myData.size());
	myData.erase(static_cast<size_t>(aIndex) + myData.begin());
}

template<typename T>
inline size_t List<T>::Size() const
{
	return myData.size();
}

template<typename T>
inline bool List<T>::IsEmpty() const
{
	return myData.empty();
}

template<typename T>
inline void List<T>::Clear()
{
	return myData.clear();
}