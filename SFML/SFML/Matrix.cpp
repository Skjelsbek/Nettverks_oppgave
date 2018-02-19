#include "Matrix.h"
#include <cmath>

void Matrix::printV(std::vector<double>& v)
{
	std::cout << "[  ";
	for (double &d : v)
	{
		std::cout << d << "  ";
	}
	std::cout << "]\n";
}

bool Matrix::swapRows(unsigned int row, unsigned int column)
{
	for (unsigned int i = row + 1; i < m_matrix.size(); i++)
	{
		if (m_matrix[i][column] != 0.f)
		{
			std::vector<double> temp = m_matrix[i];
			m_matrix[i] = m_matrix[row];
			m_matrix[row] = temp;
			return true;
		}
	}
	return false;
}

void Matrix::operator~()
{
	for (unsigned int i = 0; i < m_matrix.size(); i++) // i is the index of the rows in the matrix.
	{
		double pos0 = m_matrix[i][i]; // Get 1 at position 0.
		if (pos0 == 0 && !swapRows(i, i))
			continue;
		for (unsigned int j = 0; j < m_matrix[i].size() - i; j++) //j is the index of the colons in the matrix.
		{
			if (isnan(pos0))
				std::cout << "DEBUG\n";
			m_matrix[i][i + j] /= pos0;
		}
		for (unsigned int k = 0; k < m_matrix.size(); k++) // k is the index of the rows below row i.
		{
			if (k != i)
			{
				double nr = m_matrix[k][i];
				for (unsigned int l = 0; l < m_matrix[k].size(); l++) // l is index of columns.
				{
					m_matrix[k][l] = m_matrix[k][l] - (m_matrix[i][l] * nr);
				}
			}
		}
	}
}

void Matrix::add(double x, double y)
{
	std::vector<double> v;
	//v.push_back(powf(x, 20));
	//v.push_back(powf(x, 19));
	//v.push_back(powf(x, 18));
	//v.push_back(powf(x, 17));
	//v.push_back(powf(x, 16));
	//v.push_back(powf(x, 15));
	//v.push_back(powf(x, 14));
	//v.push_back(powf(x, 13));
	//v.push_back(powf(x, 12));
	//v.push_back(powf(x, 11));
	//v.push_back(powf(x, 10));
	v.push_back(powf(x, 9));
	v.push_back(powf(x, 8));
	v.push_back(powf(x, 7));
	v.push_back(powf(x, 6));
	v.push_back(powf(x, 5));
	v.push_back(powf(x, 4));
	v.push_back(powf(x, 3));
	v.push_back(powf(x, 2));
	v.push_back(x);
	v.push_back(1);
	v.push_back(y);
	m_matrix.push_back(v);
}

std::vector<double> Matrix::getGaused()
{
	std::vector<double> v;
	for (unsigned int i = 0; i < m_matrix.size(); i++)
	{
		v.push_back(m_matrix[i][m_matrix[i].size() - 1]);
	}
	return v;
}
void Matrix::printGauss()
{
	std::vector<double> v = getGaused();
	for (unsigned int i = 0; i < v.size(); i++)
	{
		std::cout << v[i] << '\n';
	}
}
//void Matrix::operator~()
//{
//	for (unsigned int i = 0; i < m_matrix.size(); i++) // i is the index of the rows in the matrix.
//	{
//		float pos0 = m_matrix[i][i]; // Get 1 at position 0.
//		for (unsigned int j = 0; j < m_matrix[i].size() - i; j++) //j is the index of the colons in the matrix.
//		{
//			m_matrix[i][i + j] /= pos0;
//		}
//		for (unsigned int k = i + 1; k < m_matrix.size(); k++) // k is the index of the rows below row i.
//		{
//			float nr = m_matrix[k][i];
//			for (unsigned int l = i; l < m_matrix[k].size(); l++) // l is index of colons.
//			{
//				m_matrix[k][l] = m_matrix[k][l] - (m_matrix[i][l] * nr);
//			}
//		}
//	}
//}

void Matrix::printM()
{
	for (std::vector<double> &v : m_matrix)
	{
		printV(v);
	}
}
