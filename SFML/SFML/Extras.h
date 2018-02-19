#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

namespace esf
{
	sf::RectangleShape getLine(const sf::Vector2f &point1, const sf::Vector2f &point2, float thickness = 1.0f, const sf::Color &color = sf::Color::White);

	template <class T>
	std::string toStr(T t);
	//sf::ConvexShape getShape(const Polygon2D &poly, const sf::Color &color = sf::Color::White);

	template<class T>
	std::string toStr(T t)
	{
		std::stringstream ss;
		ss << t;
		return ss.str();
	}

	void readCSV(std::vector<sf::Vector2f> &temp, std::vector<sf::Vector2f> &hum);
}