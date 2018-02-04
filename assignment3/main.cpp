#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <string>
#include <map>
#include <cmath>

using namespace std;

typedef struct Star {
	long long x;
	long long y;
} Star;

Star* majorityElement(vector<Star*> stars, long long d);
int occurrences(vector<Star*> stars, Star* targetStar, long long d);

/*
 * Algorithm for majority elements. Method was taken from the slides.
 * Used the pseudo code from slide number 4
 */
int main ()
{
	string buffer, d_k;
	char sizes[2048];
	long long d, k, differential, occurrences = 0;
	long long dSquared;
	vector<Star*> stars;
	Star* star, *majority, *s;

	// get n and k
	cin.getline(sizes, 2048);

	// make the first line a string
	d_k += sizes;

	// extract both d and k respectively
	d = stoll(d_k.substr(0, d_k.find(" ")));
	k = stoll(d_k.substr(d_k.find(" "), d_k.length()));

	if(k == 0)
	{
		cout << "NO" << endl;
	}
	else if(k == 1)
	{
		cout << 1 << endl;
	}

	dSquared = pow(d, 2);

	for(int i = 0; i < k; i++)
	{
		getline(cin, buffer);
		star = new Star;
		star->x = stoll(buffer.substr(0, buffer.find(" ")));
		star->y = stoll(buffer.substr(buffer.find(" "), buffer.length()));
		stars.push_back(star);
	}

	majority = majorityElement(stars, dSquared);

	if(majority == NULL)
	{
		cout << "NO" << endl;
	}
	else
	{
		for(int i = 0; i < k; i++)
		{
			s = stars[i];

			differential = pow((majority->x - s->x), 2) + pow((majority->y - s->y), 2);

			if(differential <= dSquared)
			{
				occurrences++;
			}
		}

		if(occurrences < stars.size() / 2)
		{
			cout << "NO" << endl;
		}
		else
		{
			cout << occurrences << endl;
		}
	}
}

Star* majorityElement(vector<Star*> stars, long long dSquared)
{
	int mid, occurrencesS1, occurrencesS2;
	Star* s1, *s2;

	if(stars.size() == 0)
	{
		return NULL;
	}
	else if(stars.size() == 1)
	{
		return stars[0];
	}
	else if(stars.size() == 2)
	{
		if(pow((stars[0]->x - stars[1]->x), 2) + pow((stars[0]->y - stars[1]->y), 2) <= dSquared)
		{
			return stars[0];
		}
		else
		{
			return NULL;
		}
	}
	else
	{
		vector<Star*> A1;
		vector<Star*> A2;

		mid = stars.size() / 2;

		for(int i = 0; i < mid; i++)
		{
			A1.push_back(stars[i]);
		}

		for(int i = mid; i < stars.size(); i++)
		{
			A2.push_back(stars[i]);
		}

		s1 = majorityElement(A1, dSquared);
		s2 = majorityElement(A2, dSquared);

		if(s1 == NULL && s2 == NULL)
		{
			return NULL;
		}
		else if(s1 == NULL)
		{
			occurrencesS2 = occurrences(stars, s2, dSquared);

			if(occurrencesS2 > stars.size() / 2)
			{
				return s2;
			}
		}
		else if(s2  == NULL)
		{
			occurrencesS1 = occurrences(stars, s1, dSquared);

			if(occurrencesS1 > stars.size() / 2)
			{
				return s1;
			}
		}
		else
		{
			occurrencesS1 = occurrences(stars, s1, dSquared);
			occurrencesS2 = occurrences(stars, s2, dSquared);

			if(occurrencesS1 > stars.size() / 2)
			{
				return s1;
			}
			else if(occurrencesS2 > stars.size() / 2)
			{
				return s2;
			}
		}
		return NULL;
	}

}

int occurrences(vector<Star*> stars, Star* targetStar, long long dSquared)
{
	int count  = 0;
	long long differential;
	Star* s;

	for(int i = 0; i < stars.size();i++)
	{
		s = stars[i];

		differential = pow((targetStar->x - s->x), 2) + pow((targetStar->y - s->y), 2);

		if(differential <= dSquared)
		{
			count ++;
		}
	}

	return count;
}