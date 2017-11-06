#include "HashMap.h"
#include <iostream>
#include <string>

void update()
{
	std::cout << "updating\n";
}

void check_temp()
{
	std::cout << "temp\n";
}

void check_hum()
{
	std::cout << "hum\n";
}

void disconnect()
{
	std::cout << "disconnecting\n";
}

int main()
{
	/*std::string test[] = { "update", "check_temp", "check_hum", "disconnect" };
	HashMap<std::string, void(*)(void)> map;
	map.append("update", update);
	map.append("temp", check_temp);
	map.append("hum", check_hum);
	map.append("discon", disconnect);
	map.run("update");
	map.run("hum");
	map.run("discon");
	map.run("temp");*/


	std::string s1 = "snicker1";
	std::string s2 = "snicker2";
	std::string s3 = "snicker3";

	LinkedList<std::string, void(*)(void)> nilsList;
	nilsList.append(s1, update);
	nilsList.append(s2, check_hum);
	nilsList.append(s3, check_temp);
	nilsList.find(s3);
	nilsList.get(s1)();
	nilsList.get(s2)();
	nilsList.get(s3)();
	system("pause");
}