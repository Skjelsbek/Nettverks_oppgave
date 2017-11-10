#pragma once

template <class KEY, class VALUE>
class LinkedList
{
private:
	LinkedList *m_next; // Next object in the list
	KEY m_key; // The key of this object
	VALUE m_value; // The value of this object
	VALUE m_default; // Default value that is returned when key not found in list
	bool m_set; // Determines if the key and value is already set
public:
	LinkedList();
	LinkedList(const LinkedList<KEY, VALUE> &other); // Copy constructor
	~LinkedList();

	LinkedList<KEY, VALUE> &operator=(const LinkedList<KEY, VALUE> &other); // = operator to set one linked list equal to another 

	void append(const KEY &key, const VALUE &value);
	VALUE &get(const KEY &key);
	void setDefault(const VALUE &value);
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
	// Placing the value at the correct place in the list
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
		m_next->setDefault(m_default);
	}
	else
	{
		m_next->append(key, value);
	}
}

template<class KEY, class VALUE>
inline VALUE &LinkedList<KEY, VALUE>::get(const KEY &key)
{
	// Returns the correct value
	if (m_key == key)
		return m_value;
	if (m_next != 0)
		return m_next->get(key);
	return m_default;
}

template<class KEY, class VALUE>
inline void LinkedList<KEY, VALUE>::setDefault(const VALUE & value)
{
	// Setting default for every object in the linked list
	m_default = value;
	if (m_next != 0)
		m_next->setDefault(value);
}