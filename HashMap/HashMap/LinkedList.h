#pragma once

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
	LinkedList(const LinkedList<KEY, VALUE> &other);
	~LinkedList();

	LinkedList<KEY, VALUE> &operator=(const LinkedList<KEY, VALUE> &other);

	void append(const KEY &key, const VALUE &value);
	VALUE &get(const KEY &key);
	bool &find(const KEY &key);
};

template<class KEY, class VALUE>
inline LinkedList<KEY, VALUE>::LinkedList()
{
	m_next = 0;
	m_set = false;
}

template<class KEY, class VALUE>
inline LinkedList<KEY, VALUE>::LinkedList(const LinkedList<KEY, VALUE>& other)
{
	m_next = 0;
	*this = other;
}

template<class KEY, class VALUE>
inline LinkedList<KEY, VALUE>::~LinkedList()
{
	delete m_next;
}

template<class KEY, class VALUE>
inline LinkedList<KEY, VALUE>& LinkedList<KEY, VALUE>::operator=(const LinkedList<KEY, VALUE>& other)
{
	delete m_next;
	m_key = other.m_key;
	m_value = other.m_value;
	m_set = other.m_set;
	m_next = new LinkedList<KEY,VALUE>;
	*m_next = *other.m_next;
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
}

template<class KEY, class VALUE>
inline bool & LinkedList<KEY, VALUE>::find(const KEY &key)
{
	if (m_key == key)
		return true;
	if (m_next != 0)
		return m_next->find(key);
	return false;
}
