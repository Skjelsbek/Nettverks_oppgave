#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <map>

//void f(void (*func) (double, int))
//{
//
//}

class HashMap
{
public:
	HashMap();
	~HashMap();
	void append(const std::string &key, void(*)(void));
	void run(const std::string &key);

private:	
	std::list<void(*)(void)> m_map[10];
	unsigned int m_size = 10;
	unsigned int getIndex(const std::string &key);
};

