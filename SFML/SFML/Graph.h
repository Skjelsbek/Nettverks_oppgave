#pragma once
#include <vector>
#include <SFML\Graphics.hpp>
//#include "Extras.h"

class Graph
{
private:
	float(*m_func)(float, float*, const unsigned int);
	sf::Color m_color;
	std::vector<float> m_params;

public:
	inline Graph() { }
	inline Graph(float(*func)(float, float*, const unsigned int), const sf::Color &color = sf::Color::Black) { set(func, color); }

	void set(float(*func)(float, float*, const unsigned int), const sf::Color &color = sf::Color::Black);
	inline void setColor(const sf::Color &color) { m_color = color; }
	inline void setParams(const std::vector<float> &params) { m_params = params; }

	void draw(sf::RenderWindow &window, const sf::Vector2f &origo, float x_spacing, float y_spacing);
};