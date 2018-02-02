#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <string>
#include <unordered_map>
#include <cmath>

using namespace std;

struct Star {
	long long x;
	long long y;
};

int majorityElement(vector<Star> stars, int d);

int main ()
{
	string buffer, d_k;
	char sizes[2048];
	int d, k, majority;
	vector<Star> stars;
	Star star;

	// get n and k
	cin.getline(sizes, 2048);

	// make the first line a string
	d_k += sizes;

	// extract both n and k respectively
	d = stoi(d_k.substr(0, d_k.find(" ")));
	k = stoi(d_k.substr(d_k.find(" "), d_k.length()));


	for(int i = 0; i < k; i++)
	{
		getline(cin, buffer);
		star.x = stoi(buffer.substr(0, buffer.find(" ")));
		star.y = stoi(buffer.substr(buffer.find(" "), buffer.length()));
		stars.push_back(star);
	}

	majority = majorityElement(stars, d);

	cout << majority << k << endl;

	if(majority > k/2)
	{
		cout << majority << endl;
	}
	else
	{
		cout << "NO" << endl;
	}
}

int majorityElement(vector<Star> stars, int d)
{
	unordered_map<int, int> majority;
	Star s1, s2;
	int distance;
	pair<int, int> star;

	int k = stars.size();

	for(int i = 0; i < k; i++)
	{
		if((i + 1) >= k)
		{
			break;
		}

		s1 = stars[i];
		s2 = stars[i + 1];

		distance = pow((s1.x - s2.x), 2) + pow((s1.y - s2.y), 2);

		if(distance <= d)
		{
			star = make_pair(i, distance);
			majority.insert(star);
		}
	}

	return majority.size();
}