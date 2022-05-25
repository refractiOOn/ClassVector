#include "Vector.hpp"
#include <iostream>

#include <vector>

int main()
{
	Vector<int> vec1(10, 4), vec2(20, 3);
	vec1.Swap(vec2);

	for (size_t i = 0; i < vec1.Size(); ++i)
	{
		std::cout << vec1[i] << std::endl;
	}

	std::cout << std::endl;

	for (int i = 0; i < vec2.Size(); ++i)
	{
		std::cout << vec2[i] << std::endl;
	}
}
