#pragma once
#include "LinkedList.h"

template <class KEY, class VALUE>
class HashMap
{
public:
	void append(const KEY &key, const VALUE &value);
	VALUE &get(const KEY &key);
	void setDefault(const VALUE &value);
private:	
	LinkedList<KEY, VALUE> m_map[10];
	unsigned int m_size = 10;
	unsigned int getIndex(const KEY &key);
};

template <class KEY, class VALUE>
unsigned int HashMap<KEY, VALUE>::getIndex(const KEY &key)
{
	// Returns the index which determines where the value shall be placed
	int index = std::hash<KEY>{}(key) % m_size; // Hashing the key and mod the hash value by the map size, to keep it in bound
	unsigned int absIndex = abs(index); // Since index might be negative we need to take the absolute value of it
	return absIndex;
}

template <class KEY, class VALUE>
void HashMap<KEY, VALUE>::append(const KEY &key, const VALUE &value)
{
	// Grabbing index and append the value in the correct linked list
	unsigned int index = getIndex(key);
	m_map[index].append(key, value);
}

template <class KEY, class VALUE>
VALUE &HashMap<KEY,VALUE>::get(const KEY &key)
{
	// Grabbing the index of the key, and grabbing the value at that index
	unsigned int index = getIndex(key);	
	return m_map[index].get(key);	
}

template<class KEY, class VALUE>
inline void HashMap<KEY, VALUE>::setDefault(const VALUE &value)
{	
	// Setting default for every linked list in the map
	for (unsigned int i = 0; i < 10; i++)
	{
		m_map[i].setDefault(value);
	}
}
