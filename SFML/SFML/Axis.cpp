#include "Axis.h"
#include <iostream>

//void Axis::setMarks(float spacing, const sf::Color &color)
//{
//	float line_height = 6.0f;
//
//	float mark_spot = (int)(m_y_axis.getPosition().x) % (int)(spacing);
//
//	while (mark_spot < m_window->getSize().x)
//	{
//		m_x_axis_marks.push_back(esf::getLine(sf::Vector2f(mark_spot, m_x_axis.getPosition().y - line_height / 2),
//											  sf::Vector2f(mark_spot, m_x_axis.getPosition().y + line_height / 2), 1.0f, color));
//		mark_spot += spacing;
//	}
//
//	mark_spot = (int)(m_x_axis.getPosition().y) % (int)(spacing);
//
//	while (mark_spot < m_window->getSize().y)
//	{
//		m_y_axis_marks.push_back(esf::getLine(sf::Vector2f(m_y_axis.getPosition().x - line_height / 2, mark_spot),
//											  sf::Vector2f(m_y_axis.getPosition().x + line_height / 2, mark_spot), 1.0f, color));
//
//		mark_spot += spacing;
//	}
//}

//void Axis::drawXmarks(float _spacing, const sf::Color &color, float line_length, float line_thickness)
//{
//	sf::RectangleShape line_marker = esf::getLine(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(0.0f, line_length), line_thickness, color);
//
//	int spacing = (int)(roundf(_spacing));
//
//	float x_mark_spot = (float)((int)(roundf(m_y_axis.getPosition().x)) % spacing);
//	float y_mark_spot = (m_x_axis.getPosition().y - (line_length / 2.0f));
//
//	//m_text.setString("TEST");
//	//m_text.setString(esf::toStr(count++));
//	//m_text.setPosition(sf::Vector2f(400, 400));
//	//m_window->draw(m_text);
//
//	int count = -(int)(roundf(m_y_axis.getPosition().x / spacing));
//	while (x_mark_spot < m_window->getSize().x)
//	{
//		line_marker.setPosition(sf::Vector2f(x_mark_spot, y_mark_spot));
//		//m_text.setString("TEST");
//		m_text.setString(esf::toStr(count++));
//		m_text.setPosition(sf::Vector2f(x_mark_spot, y_mark_spot + 10));
//		m_window->draw(line_marker);
//		m_window->draw(m_text);
//		x_mark_spot += spacing;
//	}
//}

//void Axis::drawXmarks(float _spacing, const sf::Color &color, float line_length, float line_thickness)
//{
//	sf::RectangleShape line_marker = esf::getLine(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(0.0f, line_length), line_thickness, color);
//
//	int spacing = (int)(roundf(m_x_mark_spacing));
//
//	float y_mark_spot = m_x_axis.getPosition().y - (line_length / 2.0f);
//	float x_mark_spot = (float)((int)(roundf(m_y_axis.getPosition().x)));
//	int count = 0;
//
//	while (x_mark_spot > 0) //From origo to the left.
//	{
//		line_marker.setPosition(sf::Vector2f(x_mark_spot, y_mark_spot));
//		m_text.setString(esf::toStr(count--));
//		m_text.setPosition(sf::Vector2f(x_mark_spot - 5, y_mark_spot + 10));
//		m_window->draw(line_marker);
//		m_window->draw(m_text);
//		x_mark_spot -= spacing;
//	}
//
//	x_mark_spot = (float)((int)(roundf(m_y_axis.getPosition().x)));
//	count = 0;
//
//	while (x_mark_spot < m_window->getSize().x) //From origo to the right.
//	{
//		line_marker.setPosition(sf::Vector2f(x_mark_spot, y_mark_spot));
//		m_text.setString(esf::toStr(count++));
//		m_text.setPosition(sf::Vector2f(x_mark_spot - 5, y_mark_spot + 10));
//		m_window->draw(line_marker);
//		m_window->draw(m_text);
//		x_mark_spot += spacing;
//	}
//}

void Axis::drawXmarks(float _spacing, const sf::Color &color, float line_length, float line_thickness)
{
	sf::RectangleShape line_marker = esf::getLine(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(0.0f, line_length), line_thickness, color);

	int spacing = (int)(roundf(x_group()));

	//int spacing = (int)(roundf(m_x_mark_spacing));

	float y_mark_spot = m_x_axis.getPosition().y - (line_length / 2.0f);
	float x_mark_spot = (float)((int)(roundf(m_y_axis.getPosition().x)));
	int count = 0;

	while (x_mark_spot > 0) //From origo to the left.
	{
		line_marker.setPosition(sf::Vector2f(x_mark_spot, y_mark_spot));
		m_text.setString(esf::toStr(count));
		m_text.setPosition(sf::Vector2f(x_mark_spot - 5, y_mark_spot + 10));
		m_window->draw(line_marker);
		m_window->draw(m_text);
		x_mark_spot -= spacing;
		count -= x_group.getGroupValue();
	}

	x_mark_spot = (float)((int)(roundf(m_y_axis.getPosition().x)));
	count = 0;

	while (x_mark_spot < m_window->getSize().x) //From origo to the right.
	{
		line_marker.setPosition(sf::Vector2f(x_mark_spot, y_mark_spot));
		m_text.setString(esf::toStr(count));
		m_text.setPosition(sf::Vector2f(x_mark_spot - 5, y_mark_spot + 10));
		m_window->draw(line_marker);
		m_window->draw(m_text);
		x_mark_spot += spacing;
		count += x_group.getGroupValue();
	}
}

//void Axis::drawYmarks(float _spacing, const sf::Color &color, float line_length, float line_thickness)
//{
//	sf::RectangleShape line_marker = esf::getLine(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(line_length, 0.0f), line_thickness, color);
//
//	int spacing = (int)(roundf(_spacing));
//
//	float x_mark_spot = m_y_axis.getPosition().x - (line_length / 2.0f);
//	float y_mark_spot = (float)((int)(roundf(m_x_axis.getPosition().y)) % spacing);
//
//	while (y_mark_spot < m_window->getSize().y)
//	{
//		line_marker.setPosition(sf::Vector2f(x_mark_spot, y_mark_spot));
//		m_window->draw(line_marker);
//		y_mark_spot += spacing;
//	}
//}

//void Axis::drawYmarks(float _spacing, const sf::Color &color, float line_length, float line_thickness)
//{
//	sf::RectangleShape line_marker = esf::getLine(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(line_length, 0.0f), line_thickness, color);
//
//	int spacing = (int)(roundf(m_y_mark_spacing));
//
//	float x_mark_spot = m_y_axis.getPosition().x - (line_length / 2.0f);
//	float y_mark_spot = (float)((int)(roundf(m_x_axis.getPosition().y)));
//	int count = 0;
//
//	while (y_mark_spot > 0) //From origo and up.
//	{
//		line_marker.setPosition(sf::Vector2f(x_mark_spot, y_mark_spot));
//		m_text.setString(esf::toStr(-count--));
//		m_text.setPosition(sf::Vector2f(x_mark_spot - 10, y_mark_spot - 5));
//		m_window->draw(line_marker);
//		m_window->draw(m_text);
//		y_mark_spot -= spacing;
//	}
//
//	y_mark_spot = (float)((int)(roundf(m_x_axis.getPosition().y)));
//	count = 0;
//
//	while (y_mark_spot < m_window->getSize().x) //From origo and down.
//	{
//		line_marker.setPosition(sf::Vector2f(x_mark_spot, y_mark_spot));
//		m_text.setString(esf::toStr(-count++));
//		m_text.setPosition(sf::Vector2f(x_mark_spot - 10, y_mark_spot - 5));
//		m_window->draw(line_marker);
//		m_window->draw(m_text);
//		y_mark_spot += spacing;
//	}
//}

void Axis::drawYmarks(float _spacing, const sf::Color &color, float line_length, float line_thickness)
{
	sf::RectangleShape line_marker = esf::getLine(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(line_length, 0.0f), line_thickness, color);

	int spacing = (int)(roundf(y_group()));

	float x_mark_spot = m_y_axis.getPosition().x - (line_length / 2.0f);
	float y_mark_spot = (float)((int)(roundf(m_x_axis.getPosition().y)));
	int count = 0;

	while (y_mark_spot > 0) //From origo and up.
	{
		line_marker.setPosition(sf::Vector2f(x_mark_spot, y_mark_spot));
		m_text.setString(esf::toStr(-count));
		m_text.setPosition(sf::Vector2f(x_mark_spot - 20, y_mark_spot - 5));
		m_window->draw(line_marker);
		m_window->draw(m_text);
		y_mark_spot -= spacing;
		count -= y_group.getGroupValue();
	}

	y_mark_spot = (float)((int)(roundf(m_x_axis.getPosition().y)));
	count = 0;

	while (y_mark_spot < m_window->getSize().x) //From origo and down.
	{
		line_marker.setPosition(sf::Vector2f(x_mark_spot, y_mark_spot));
		m_text.setString(esf::toStr(-count));
		m_text.setPosition(sf::Vector2f(x_mark_spot - 20, y_mark_spot - 5));
		m_window->draw(line_marker);
		m_window->draw(m_text);
		y_mark_spot += spacing;
		count += y_group.getGroupValue();
	}
}

Axis::Axis(sf::RenderWindow &window, float *x_spacing_groups, unsigned int x_spacing_groups_size, float *y_spacing_groups, unsigned int y_spacing_groups_size,
	const sf::Color &color, float x_mark_spacing, float y_mark_spacing)
{
	m_window = &window;

	float x_size = (float)(m_window->getSize().x);
	float y_size = (float)(m_window->getSize().y);

	m_x_axis = esf::getLine(sf::Vector2f(0.0f, y_size / 2.0f), sf::Vector2f(x_size, y_size / 2.0f), 1.0f, color);
	//m_y_axis = esf::getLine(sf::Vector2f(20.0f, 0.0f), sf::Vector2f(20.0f, y_size), 1.0f, color);
	m_y_axis = esf::getLine(sf::Vector2f(x_size / 3.0f, 0.0f), sf::Vector2f(x_size / 3.0f, y_size), 1.0f, color);
	move(sf::Vector2f(-220, 0));

	m_x_mark_spacing = x_mark_spacing;
	m_y_mark_spacing = y_mark_spacing;
	//setMarks(spacing, color);

	x_group.set(x_spacing_groups, x_spacing_groups_size, x_mark_spacing);
	y_group.set(y_spacing_groups, y_spacing_groups_size, y_mark_spacing);

	scaleX(5.7f);
	scaleY(.4f);

	//sf::Font font;
	if (!m_font.loadFromFile("fonts/times.ttf"))
		throw std::runtime_error("Font not found.");
	m_text.setFont(m_font);
	m_text.setCharacterSize(10);
	m_text.setFillColor(sf::Color::Black);

}

void Axis::setColor(const sf::Color &color)
{
	m_x_axis.setFillColor(color);
	m_y_axis.setFillColor(color);
}

void Axis::scaleX(float scale_value)
{
	x_group.scale(scale_value);
}

void Axis::scaleY(float scale_value)
{
	y_group.scale(scale_value);
}

void Axis::scale(float scale_value)
{
	scaleX(scale_value);
	scaleY(scale_value);
}

void Axis::move(const sf::Vector2f & vector)
{
	m_x_axis.move(0, vector.y);
	m_y_axis.move(vector.x, 0);
}

void Axis::addGraph(const Graph &graph)
{
	m_graphs.push_back(graph);
	//m_graphs[m_graphs.size() - 1].update(sf::Vector2f(m_y_axis.getPosition().x, m_x_axis.getPosition().y), m_x_mark_spacing, m_y_mark_spacing);
}

void Axis::draw()
{
	m_window->draw(m_x_axis);
	m_window->draw(m_y_axis);

	drawXmarks(m_x_mark_spacing, m_x_axis.getFillColor());
	drawYmarks(m_y_mark_spacing, m_y_axis.getFillColor());

	for (Graph &g : m_graphs)
	{
		//g.draw(*m_window, sf::Vector2f(m_y_axis.getPosition().x, m_x_axis.getPosition().y), m_x_mark_spacing, m_y_mark_spacing);
		g.draw(*m_window, sf::Vector2f(m_y_axis.getPosition().x, m_x_axis.getPosition().y), x_group.getScale(), y_group.getScale());
	}

	//setupDraw(spacing, m_x_axis.getFillColor());

	//for (const sf::RectangleShape &xMark : m_x_axis_marks)
	//	m_window->draw(xMark);
	//for (const sf::RectangleShape &yMark : m_y_axis_marks)
	//	m_window->draw(yMark);
}
