#include "Extras.h"

namespace esf
{
	sf::RectangleShape getLine(const sf::Vector2f &point1, const sf::Vector2f &point2, float thickness, const sf::Color &color)
	{
		float length = sqrt(pow(point2.x - point1.x, 2.0f) + pow(point2.y - point1.y, 2.0f));
		float angle = (180.0f / 3.141592653589793f) * atan2f(point2.y - point1.y, point2.x - point1.x);

		sf::RectangleShape rect(sf::Vector2f(length, thickness));
		rect.setPosition(point1);
		rect.setRotation(angle);
		rect.setFillColor(color);
		return rect;
	}

	void readCSV(std::vector<sf::Vector2f> &temp, std::vector<sf::Vector2f> &hum)
	{
		std::fstream file;
		file.open("../../Client/Client/log.csv", std::ios::in);

		file.seekg(0, file.end);
		int len = file.tellg();

		file.seekg(0, file.beg);
		
		char *data = new char[len];
		file.read(data, len);
		int commaCount = 0;
		int digitCount = 0;
		std::string firstDigit;
		std::string secondDigit;
		std::string tmpTemp;
		std::string tmpHum;

		float fTime;
		float fTemp;
		float fHum;

		int j = 0;
		int i = 0;
		while (j < len)
		{
			if (data[i] == '\n')
				i++;
			while (data[i] != '\n' && i < len)
			{
				if (data[i] == ',')
				{
					commaCount++;
				}
				else if (commaCount == 1 && data[i] != ':')
				{
					if (digitCount < 2)
					{
						firstDigit.push_back(data[i]);
						digitCount++;
					}
					else
					{
						secondDigit.push_back(data[i]);
					}
				}
				else if (commaCount == 2)
				{
					tmpTemp.push_back(data[i]);
				}
				else if (commaCount == 3)
				{
					tmpHum.push_back(data[i]);
				}
				i++;
			}
			if (firstDigit.size() != 0 && secondDigit.size() != 0 && tmpTemp.size() != 0 && tmpHum.size() != 0)
			{
				fTime = std::stof(firstDigit)*60;
				fTime += std::stof(secondDigit);
				fTemp = std::stof(tmpTemp);
				fHum = std::stof(tmpHum);
		
				temp.push_back(sf::Vector2f(fTime, fTemp));
				hum.push_back(sf::Vector2f(fTime, fHum));
			}

			j = i + 1;

			commaCount = 0;
			digitCount = 0;
			firstDigit = "";
			secondDigit = "";
			tmpTemp = "";
			tmpHum = "";
		}
		
		if (!file)
		{
			std::cerr << "I am sooory, sometime things go south...\n";
		}

		//for (unsigned int i = 0; i < len; i++)
		//{
		//	std::cout << arr[i] << '\n';
		//}
		delete[] data;
	}

	//sf::ConvexShape getShape(const Polygon2D &poly, const sf::Color &color)
	//{
	//	sf::ConvexShape shape(poly.size());

	//	for (int i = 0; i < poly.size(); i++)
	//	{
	//		shape.setPoint(i, sf::Vector2f(poly.get(i).get().x, poly.get(i).get().y));
	//	}
	//	shape.setFillColor(color);

	//	return shape;
	//}
}