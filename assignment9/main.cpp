#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <limits>


typedef std::pair <int, int> hotel;

int main ()
{
	std::ios::sync_with_stdio(false);
	std::cin.tie(NULL);

	int n, d, next, penalty;
	std::vector<hotel> hotels;

	std::cin >> n;

	for(int i = 0; i < n + 1; i++)
	{
		std::cin >> d;
		hotels.push_back(std::make_pair(d, std::numeric_limits<int>::max()));
	}

	hotels.at(0).second = 0;

	for(int i = 0; i < hotels.size(); i++)
	{
		next = i + 1;

		while(next < hotels.size() && (hotels.at(next).first - hotels.at(i).first) < 600)
		{
			penalty = hotels.at(i).second + pow((400 - (hotels.at(next).first - hotels.at(i).first)), 2);

			if(penalty < hotels.at(next).second)
			{
				hotels.at(next).second = penalty;
			}

			next += 1;
		}
	}

	std::cout << hotels.back().second;

	return 0;	
}