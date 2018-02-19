#pragma once
//#include <time.h>
#include <SFML/Graphics.hpp>

class Object
{
private:
	//Basic attributes.
	unsigned int &a_size;
	unsigned int a_my_index;
	sf::Shape *a_shapes;
	sf::RectangleShape m_shape;

	//Physics attributes.
	sf::Vector2f m_velocity;
	sf::Vector2f m_acceleration;
	bool m_run_gravity;

	void runGravity();
	bool doStopGravity();

	bool checkBottomCollide();
	bool bottomCollide(sf::Shape &other_shape);

	//Time attributes.

	clock_t m_gravity_time = clock();

public:
	Object(unsigned int &size, sf::Shape *shapes, unsigned int my_index, const sf::RectangleShape &shape = sf::RectangleShape());
};