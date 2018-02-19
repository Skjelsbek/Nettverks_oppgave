#include "SpaceScaling.h"
#include <iostream>

//Private:
void SpaceScaling::moveIndex(unsigned int change)
{
	unsigned int new_index = m_index + change;
	if (new_index < 0)
		new_index = 0;
	else if (new_index >= m_size)
		new_index = m_size - 1;
	m_index = new_index;
}

//Public:
void SpaceScaling::set(float *group, unsigned int size, float scale, unsigned int start_index)
{
	m_group = group;
	m_size = size;
	m_scale = scale;
	m_index = start_index;
}

//void SpaceScaling::scale(float _scale)
//{
//	float new_scale = _scale * m_scale;
//
//	if (new_scale < 5.0f) //Maximum
//	{
//		new_scale = 5.0f;
//		m_index = m_size - 1;
//	}
//	else if (new_scale > m_group[m_index+1]) // Decrease index.
//		moveIndex(-1);
//	else if (new_scale < m_group[m_index]) // Increase index.
//	{
//		if (m_index == m_size - 1) // Minimum.
//			new_scale = m_group[m_index];
//		else
//			moveIndex(1);
//	}
//	m_scale = new_scale;
//	std::cout << "DEBUG: " << m_scale << " | " << m_index << "\n";
//}

void SpaceScaling::scale(float _scale)
{
	float new_scale = _scale * m_scale;

	if (_scale < 1) // Zoom out.
	{
		if (new_scale < 0.1f) //Maximum
		{
			new_scale = 0.1f;
			m_index = m_size - 1;
		}
		else if (new_scale*m_group[m_index] < 10.0f)
		{
			moveIndex(1);
		}
	}
	else if (_scale > 1) // Zoom in.
	{
		if (new_scale > 100.0f) //Minimum
		{
			new_scale = 100.0f;
			m_index = 0;
		}
		else if (new_scale*m_group[m_index] > 100.0f)
		{
			moveIndex(-1);
		}
	}
	m_scale = new_scale;

	//std::cout << "DEBUG: " << m_scale << "  |  " << m_index << '\n';
}
