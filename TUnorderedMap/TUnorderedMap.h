#pragma once
#include <iostream>
using namespace std;
#define min_capacity 3



template <typename Type>
class MapElement
{
public:
	Type Element;
	bool isHashed = false;
	MapElement() = default;
	MapElement(Type element)
	{
		Element = element;
	}
	void operator=(Type& value)
	{
		Element = value;
	}
	/*Key& First()
	{
		return Element.first;
	}
	Value& Second()
	{
		return Element.first;
	}*/
	~MapElement() 
	{
		Element.~Type();
	};
};

template <typename TUnorderedMap>
class UMapIterator
{
public:
	using ValueType = typename TUnorderedMap::ValueType;
	using ValueTypePtr = ValueType*;
	using ValueTypeRef= ValueType&;
private:
	ValueTypePtr m_Ptr;
public:
	UMapIterator(ValueTypePtr ptr) : m_Ptr(ptr) {}
	UMapIterator& operator++()
	{
		m_Ptr++;
		return *this;
	}
	UMapIterator& operator++(int i)
	{
		UMapIterator temp = *this;
		return temp;
		m_Ptr++;
	}
	UMapIterator& operator--()
	{
		m_Ptr--;
		return *this;
	}
	UMapIterator& operator--(int i)
	{
		UMapIterator temp = *this;
		return temp;
		m_Ptr--;
	}
	ValueTypeRef operator[](size_t index)
	{
		return *(m_Ptr + index);
	}
	ValueTypePtr operator->()
	{
		return m_Ptr;
	}
	ValueTypeRef operator*()
	{
		return *m_Ptr;
	}
	bool operator ==(const UMapIterator& other) const
	{
		return m_Ptr == other.m_Ptr;
	}
	bool operator !=(const UMapIterator& other) const
	{
		return !(*this == other);
	}
};

template <typename Key, typename Value>
class TUnorderedMap
{
public:
	using Type = pair<Key, Value>;
	using ValueType = MapElement<Type>;
	using UMapIterator = typename UMapIterator<TUnorderedMap<Key, Value>>;
private:	
	size_t m_Size = 0;
	size_t m_Capacity = 0;
	MapElement<Type>* m_Table;
	void ReAlloc(size_t NewCapacity)
	{
		MapElement<Type>* new_block = new MapElement<Type>[NewCapacity]();
		MapElement<Type>* temp = m_Table;
		size_t size = m_Capacity;
		m_Capacity = NewCapacity;
		m_Table = new_block;
		for (size_t i = 0; i < size; i++)
		{
			if (temp[i].isHashed) ReinsertElement(temp[i]);
		}
		delete[] temp;
	}
	size_t GetHashKey(Type Element)
	{
		return hash<Key>()(Element.first) % m_Capacity;
	}
	size_t GetHashKey(Key keyvalue)
	{
		return hash<Key>()(keyvalue) % m_Capacity;
	}
public:
	TUnorderedMap()
	{
		ReAlloc(3);
	}
	void ReinsertElement(MapElement<Type>& Element)
	{
		size_t index = GetHashKey(Element.Element);
		if (!m_Table[index].isHashed || !m_Capacity)
		{
			m_Table[index] = move(MapElement<Type>(Element));
			m_Size++;
		}
		else
		{
			m_Size = 0;
			ReAlloc(m_Capacity + m_Capacity / 2);
			ReinsertElement(Element);
		}
	}
	void InsertElement(Type Element)
	{	
		size_t index = GetHashKey(Element);
		if (!m_Table[index].isHashed || !m_Capacity)
		{
			m_Table[index] = MapElement<Type>(Element);
			m_Table[index].isHashed = true;
			m_Size++;
		}
		else
		{
			m_Size = 0;
			ReAlloc(m_Capacity + m_Capacity / 2);
			InsertElement(Element);
		}
	}
	void Print()
	{
		cout << "StartPrint===================\n";
		for (size_t i = 0; i < m_Capacity; i++)
		{
			cout << m_Table[i].Element.first << " " << m_Table[i].Element.second 
				<< " " << m_Table[i].isHashed << endl;
		}
		cout << "EndPrint===================\n";
	}
	Type& operator[](Key keyvalue)
	{
		size_t index = GetHashKey(keyvalue);
		if (m_Table[index].isHashed) return m_Table[index].Element;
	}
	bool isEmpty()
	{
		if (m_Size) return false;
		else return true;
	}
	UMapIterator begin()
	{
		return UMapIterator(m_Table);
	}
	UMapIterator end()
	{
		return UMapIterator(m_Table + m_Capacity);
	}
	UMapIterator Find(Key key)
	{
		size_t index = GetHashKey(key);
		if (m_Table[index].isHashed) return UMapIterator(m_Table + index);
	}
	void Clear()
	{
		MapElement<Type>* temp = m_Table;
		m_Capacity = min_capacity;
		m_Table = new MapElement<Type>[m_Capacity]();
		delete[] temp;
		m_Size = 0;
	}
	~TUnorderedMap()
	{
		Clear();
		delete[] m_Table;
	}
};
