#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>

#include "Extras.h"
#include "Graph.h"
#include "Axis.h"
#include <string>
#include "Matrix.h"


float mFunc(float x, float *parameters, const unsigned int size)
{
	float sum = 0;
	for (register unsigned int i = 0; i < size; i++)
	{
		sum += parameters[i] * powf(x, (float)size - (float)i - 1.0f);
	}
	return sum;
}

void updateParams(Axis &axis)
{
	std::vector<sf::Vector2f> temp;
	std::vector<sf::Vector2f> hum;

	Matrix tempMat;
	Matrix humMat;

	esf::readCSV(temp, hum);


	for (unsigned int i = temp.size() - 10; i < temp.size(); i++)
	{
		tempMat.add(temp[i].x - temp[temp.size() - 10].x + 1.f, temp[i].y);
		humMat.add(hum[i].x - hum[temp.size() - 10].x + 1.f, hum[i].y);
	}

	~tempMat;
	~humMat;

	std::vector<float> vf1;
	std::vector<float> vf2;
	std::vector<double> vd1 = tempMat.getGaused();
	std::vector<double> vd2 = humMat.getGaused();

	for (unsigned int i = 0; i < vd1.size(); i++)
	{
		vf1.push_back((float)vd1[i]);
		vf2.push_back((float)vd2[i]);
	}

	axis.updateParams(vf1, 0);
	axis.updateParams(vf2, 1);
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");

	srand((unsigned int)time(0));

	window.setFramerateLimit(144);

	bool mouse_button_held = false;

	const unsigned int x_space_size = 4;
	float x_space[x_space_size] = { 1,10,60,600 };
	const unsigned int y_space_size = 4;
	float y_space[y_space_size] = { 1,10,100,1000 };


	Axis axis_cross(window, x_space, x_space_size, y_space, y_space_size, sf::Color::Black);

	Graph tempGraph(mFunc, sf::Color::Red);
	Graph humGraph(mFunc, sf::Color::Blue);

	sf::Vector2f mouse_moved(0.0f, 0.0f);

	axis_cross.addGraph(tempGraph);
	axis_cross.addGraph(humGraph);

	updateParams(axis_cross);

	clock_t update_timer = clock();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == 0) //Left mouse button.
				{
					mouse_button_held = true;
					mouse_moved.x = (float)event.mouseButton.x;
					mouse_moved.y = (float)event.mouseButton.y;
					axis_cross.printScale();
					//axis_cross.scaleX(0.5f);
				}
				else if (event.mouseButton.button == 1) //Right mouse button.
				{
					/*axis_cross.scaleX(2.0f);*/
				}
			}
			else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == 0)
			{
				mouse_button_held = false;
			}
			else if (mouse_button_held && event.type == sf::Event::MouseMoved)  //Mouse drag.
			{
				//axis_cross.move(sf::Vector2f(event.mouseMove.x - mouse_moved.x, event.mouseMove.y - mouse_moved.y));
				mouse_moved.x = (float)event.mouseMove.x;
				mouse_moved.y = (float)event.mouseMove.y;
				break;
			}
			else if (event.type == sf::Event::MouseWheelScrolled && event.mouseWheelScroll.delta > 0)
			{
				//axis_cross.scale(1.0f + (event.mouseWheelScroll.delta / 10.0f));
			}
			else if (event.type == sf::Event::MouseWheelScrolled && event.mouseWheelScroll.delta < 0)
			{
				//axis_cross.scaleX(1.0f / (1.0f + (event.mouseWheelScroll.delta / 10)));
				//axis_cross.scale(1.0f / pow(1.1f,-event.mouseWheelScroll.delta));
			}
		}

		if (clock() > update_timer + 5000)
		{
			updateParams(axis_cross);
			update_timer = clock();
		}


		window.clear(sf::Color(200,200,200,255));

		axis_cross.draw();

		window.display();
	}

	return 0;
}