#pragma once
#include <iostream>
#include <vector>
#include "Extras.h"
#include "Graph.h"
#include "SpaceScaling.h"

class Axis
{
private:
	sf::RectangleShape m_x_axis;
	sf::RectangleShape m_y_axis;
	//std::vector<sf::RectangleShape> m_x_axis_marks;
	//std::vector<sf::RectangleShape> m_y_axis_marks;

	sf::RenderWindow *m_window;

	std::vector<Graph> m_graphs;

	float m_x_mark_spacing;
	float m_y_mark_spacing;

	SpaceScaling x_group;
	SpaceScaling y_group;

	sf::Text m_text;
	sf::Font m_font;

	//void setMarks(float spacing, const sf::Color &color);
	void drawXmarks(float spacing, const sf::Color &color, float line_length = 6.0f, float line_thickness = 1.0f);
	void drawYmarks(float spacing, const sf::Color &color, float line_length = 6.0f, float line_thickness = 1.0f);

public:
	Axis(sf::RenderWindow &window, float *x_spacing_groups, unsigned int x_spacing_groups_size, float *y_spacing_groups, unsigned int y_spacing_groups_size, 
		 const sf::Color &color = sf::Color::White, float x_mark_spacing = 15.0f, float y_mark_spacing = 15.0f);

	void setColor(const sf::Color &color);

	void scaleX(float scale_value);
	void scaleY(float scale_value);
	void scale(float scale_value);

	void move(const sf::Vector2f &vector);

	inline void printScale() { std::cout << "X scale: " << m_x_mark_spacing << "  |  Y scale : " << m_y_mark_spacing << '\n'; }

	void addGraph(const Graph &graph);

	void updateParams(const std::vector<float> &params, unsigned int index) { m_graphs[index].setParams(params); }

	void draw();
};