#pragma once
#include <iostream>

template <class KEY, class VALUE>
class LinkedList
{
private:
	LinkedList *m_next;
	KEY m_key;
	VALUE m_value;
	bool m_set;
public:
	LinkedList();
	~LinkedList();

	void append(const KEY &key, const VALUE &value);
	VALUE &get(const KEY &key);
};

template<class KEY, class VALUE>
inline LinkedList<KEY, VALUE>::LinkedList()
{
	m_next = 0;
	m_set = false;
}

template<class KEY, class VALUE>
inline LinkedList<KEY, VALUE>::~LinkedList()
{
	delete m_next;
}

template<class KEY, class VALUE>
inline void LinkedList<KEY, VALUE>::append(const KEY &key, const VALUE &value)
{
	if (!m_set)
	{
		m_key = key;
		m_value = value;
		m_set = true;
	}
	else if (m_next == 0)
	{
		m_next = new LinkedList;
		m_next->append(key, value);
	}
	else
	{
		m_next->append(key, value);
	}
}

template<class KEY, class VALUE>
inline VALUE &LinkedList<KEY, VALUE>::get(const KEY &key)
{
	if (m_key == key)
		return m_value;
	if (m_next != 0)
		return m_next->get(key);
	throw std::runtime_error("Not found.\n");
}
