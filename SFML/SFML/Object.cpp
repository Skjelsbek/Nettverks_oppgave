#include "Object.h"

void Object::runGravity()
{
	if (m_run_gravity)
	{
		if (doStopGravity())
		{
			m_run_gravity = false;
		}
		else
		{
			if (clock() > m_gravity_time + 1000) //Wait one second between each increase.
			{
				m_acceleration.y += 9.81;
				m_velocity += m_acceleration;

				m_gravity_time = clock();
			}
		}
	}
}

bool Object::doStopGravity()
{
	if (checkBottomCollide())
		return false;
	return true;
}

bool Object::checkBottomCollide()
{
	for (int i = 0; i < a_size; i++)
	{
		if (i != a_my_index && bottomCollide(a_shapes[i]))
			return true;
	}
	return false;
}

bool Object::bottomCollide(sf::Shape &other_shape)
{
	//sf::Vector2f nw(m_shape.getSize().x, m_shape.getSize().y);
	//sf::Vector2f ne(m_shape.getSize().x + m_shape.getLocalBounds().width, m_shape.getSize().y);
	//sf::Vector2f sw(m_shape.getSize().x, m_shape.getSize().y + m_shape.getLocalBounds().height);
	//sf::Vector2f se(m_shape.getSize().x + m_shape.getLocalBounds().width, m_shape.getSize().y + m_shape.getLocalBounds().height);

	//float angle1 = atan2(m_shape.getPosition().y - other_shape.getPosition().y, m_shape.getPosition().x - m_shape.getPosition().x);
	//float angle2 = atan2(m_shape.getPosition().y - other_shape.getPosition().y, m_shape.getPosition().x - m_shape.getPosition().x);

	//if (other_shape.getRotation() > )
	return false;
}

Object::Object(unsigned int &size, sf::Shape *shapes, unsigned int my_index, const sf::RectangleShape &shape) :
	a_size(size),
	a_shapes(shapes),
	a_my_index(my_index),
	m_shape(shape) 
{
	m_velocity = { 0,0 };
	m_acceleration = { 0,0 };
	m_run_gravity = true;

	m_gravity_time = clock();
}

