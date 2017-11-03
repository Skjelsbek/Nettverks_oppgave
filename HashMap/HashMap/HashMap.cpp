#include "HashMap.h"

HashMap::HashMap()
{
}


HashMap::~HashMap()
{
}

unsigned int HashMap::getIndex(const std::string &key)
{	
	int index = std::hash<std::string>{}(key) % m_size;
	unsigned int absIndex = abs(index);
	return absIndex;
}

void HashMap::append(const std::string &key, void(*f)(void))
{
	unsigned int index = getIndex(key);
	m_map[index].append(key, f);
}

void HashMap::run(const std::string & key)
{
	unsigned int index = getIndex(key);
	m_map[index].get(key)();
}
