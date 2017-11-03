#pragma once

template <class KEY, class VALUE>
class LinkedList
{
private:
	LinkedList *m_next;
	KEY m_key;
	VALUE m_value;
public:
	LinkedList(const KEY &key, const VALUE &value);
	~LinkedList();

	void append(const KEY &key, const VALUE &value);
	VALUE &get(const KEY &key);
};

template<class KEY, class VALUE>
inline LinkedList<KEY, VALUE>::LinkedList(const KEY &key, const VALUE &value)
{
	m_next = 0;
	m_key = key;
	m_value = value;
}

template<class KEY, class VALUE>
inline LinkedList<KEY, VALUE>::~LinkedList()
{

}
