#pragma once
#include <iostream>
#include <vector>
#include <SFML\Graphics.hpp>

class Matrix
{
private:
	void printV(std::vector<double> &v);
	bool swapRows(unsigned int row, unsigned int column);
public:
	std::vector<std::vector<double>> m_matrix;
	void operator~();
	void add(double x, double y);
	inline void add(const sf::Vector2f &v) { add(v.x, v.y); }
	std::vector<double> getGaused();
	void printGauss();

	void printM();
};