#pragma once

class SpaceScaling
{
private:
	float *m_group;
	unsigned int m_size;
	unsigned int m_index;

	float m_scale;

	void moveIndex(unsigned int change);
public:
	inline SpaceScaling(){}
	inline SpaceScaling(float *group, unsigned int size, float scale, unsigned int start_index = 0) { set(group, size, scale, start_index); }

	void set(float *group, unsigned int size, float scale, unsigned int start_index = 0);

	void scale(float _scale);

	inline float operator()() { return m_scale * m_group[m_index]; } //Overload () operator, to get value at current index.
	inline float getGroupValue() { return m_group[m_index]; }
	inline float getScale() { return m_scale; }

};