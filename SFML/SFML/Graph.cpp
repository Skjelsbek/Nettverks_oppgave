#include <iostream>
#include "Graph.h"

void Graph::set(float(*func)(float, float*, const unsigned int), const sf::Color &color)
{
	m_func = func;
	m_color = color;
}

void Graph::draw(sf::RenderWindow &window, const sf::Vector2f &origo, float x_spacing, float y_spacing)
{

	float x = origo.x + 1.f * x_spacing;
	float precision = 0.05f;

	//size_t map_size = (size_t)roundf(window.getSize().x * (1 / precision));
	size_t map_size = (size_t)roundf(((origo.x + 10.0f * x_spacing) - (x)) * (1 / precision));

	//float params[] = { 0,(1.f/362880.f),0,(1.f / 5040.f),0,(1.f/120.f),0,(1.f/6.f),0,1,0 };
	//float params[] = { 0,0,0,0,0,0,0,-0.5f,3.0f,-4.5f, 26.0f };
	const unsigned int size = m_params.size();
	float *my_arr = new float[size];
	for (unsigned int i = 0; i < size; i++)
	{
		my_arr[i] = m_params[i];
	}

	sf::VertexArray point_map(sf::Points, map_size);
	for (register unsigned int i = 0; i < map_size; i++)
	{
		point_map[i].position = sf::Vector2f(x - x_spacing, origo.y - y_spacing * m_func((x - origo.x) / x_spacing, my_arr, size));
		point_map[i].color = m_color;
		x += precision;
	}
	window.draw(point_map);	

	delete[] my_arr;

	//std::cout << "x : " << origo.x + x_spacing * m_points[1000].x << "   y: " << origo.y + y_spacing * m_points[1000].y << '\n';
}
