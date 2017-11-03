#include "HashMap.h"

int main()
{
	std::string test[] = { "update", "check_temp", "check_hum", "disconnect" };
	HashMap map;
	map.append("update", update);
	map.append("temp", check_temp);
	map.append("hum", check_hum);
	map.append("discon", disconnect);

}

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