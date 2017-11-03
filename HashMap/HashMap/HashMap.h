#pragma once
#include "LinkedList.h"

template <class KEY, class VALUE>
class HashMap
{
public:
	void append(const KEY &key, const VALUE &value);
	void run(const KEY &key);

private:	
	LinkedList<KEY, VALUE> m_map[10];
	unsigned int m_size = 10;
	unsigned int getIndex(const KEY &key);
};

template <class KEY, class VALUE>
unsigned int HashMap<KEY, VALUE>::getIndex(const KEY &key)
{
	int index = std::hash<KEY>{}(key) % m_size;
	unsigned int absIndex = abs(index);
	return absIndex;
}

template <class KEY, class VALUE>
void HashMap<KEY, VALUE>::append(const KEY &key, const VALUE &value)
{
	unsigned int index = getIndex(key);
	m_map[index].append(key, value);
}

template <class KEY, class VALUE>
void HashMap<KEY,VALUE>::run(const KEY & key)
{
	unsigned int index = getIndex(key);
	m_map[index].get(key)();
}
