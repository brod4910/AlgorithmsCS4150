#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <algorithm>
#include <map>
#include <limits>

typedef std::pair<int, int> rooms;
int maxValue(int r, int uncloseableRoom, int k);

std::vector<rooms> gallery;
std::map<std::string, int> c;

int N;
bool less;

int main()
{
	std::ios::sync_with_stdio(false);
	std::cin.tie(NULL);

	int k, r1, r2, max1, max2, max3 , max;

	std::cin >> N >> k;

	for(int i = 0; i < N + 1; i++)
	{
		std::cin >> r1 >> r2;
		gallery.push_back(std::make_pair(r1, r2));
	}

	// return b == 0 ? a : gcd(b, a % b);

	if(k == N)
	{
		less = false;
		max = std::max(maxValue(0, 0, k), maxValue(0, 1, k));
		std::cout << max << std::endl;
	}
	else
	{
		less = true;
		max = std::max(maxValue(0, -1, k), std::max(maxValue(0, 0, k), maxValue(0, 1, k)));
		std::cout << max << std::endl;
	}

	return 0;
}

int maxValue(int r, int uncloseableRoom, int k)
{
	int max = std::numeric_limits<int>::min();

	if(r == N)
	{
		if(uncloseableRoom == 0 && k == 0)
		{
			return gallery[r].first;
		}
		else if(uncloseableRoom == 1 && k == 0)
		{
			return gallery[r].second;
		}
		else if(uncloseableRoom == -1 && k == 0)
		{
			return std::max(gallery[r].first, gallery[r].second);
		}
		else
		{
			return std::numeric_limits<int>::min();
		}
	}
	else
	{
		std::string s = std::to_string(r) + ' ' + std::to_string(uncloseableRoom) + ' ' + std::to_string(k);

		if(c.find(s) != c.end())
		{
			max = c.find(s)->second;
		}
		else
		{
			if(uncloseableRoom == 0)
			{
				// return gallery[r].first + maxValue(r+1, 0, k-1);
				max = std::max(gallery[r].first + maxValue(r+1, 0, k-1), (less) ? gallery[r].first + gallery[r].second + maxValue(r+1, -1, k) : 0);
			}
			else if(uncloseableRoom == 1)
			{
				// return gallery[r].second + maxValue(r+1, 1, k-1);
				max = std::max(gallery[r].second + maxValue(r+1, 1, k-1), (less) ? gallery[r].first + gallery[r].second + maxValue(r+1, -1, k) : 0);
			}
			else if(uncloseableRoom == -1)
			{
				max = std::max(gallery[r].first + gallery[r].second + maxValue(r+1, -1, k), 
					std::max(gallery[r].second + maxValue(r+1, 1, k-1), gallery[r].first + maxValue(r+1, 0, k-1)));
			}

			if(c.find(s) == c.end())
			{
				c.insert(std::make_pair(s, max));
			}
			else
			{
				max = c.find(s)->second;
			}
		}

	}

	return max;
}

