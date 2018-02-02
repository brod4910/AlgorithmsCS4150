#include <iostream>
#include <algorithm>
#include <string>
#include <map>
#include <vector>
#include <stdio.h>
#include <cstdlib>
#include <fstream>
#include <ctime>
#include <cmath>

using namespace std;
vector<string> createAnagram(int n, int k);

int main (int argc, char *argv[])
{
	clock_t timer;
	double forloopDuration;
	double totDuration;
	double prevTime = 0;
	vector <string> words;
	map <string, int> solutions;
	map <string, int>rejected;
	char sizes[256];
	string size, word;
	int n, k;
	string s;

	cin.getline(sizes, 256);
	
	size += sizes;

	n = stoi(size.substr(0, size.find(" ")));
	k = stoi(size.substr(size.find(" "), size.length()));

	// for(int i = 0; i < n; i++)
	// {
	// 	getline(cin, word);
	// 	words.push_back(word);
	// }

	printf("%s\n", "Size\tTime (msec)\tDelta");

	for(; n < 66000; n = n << 1)
	{
		timer = clock();

		for(auto it = words.begin(); it != words.end(); ++it)
		{

		}

		forloopDuration = (clock() - timer) / (double) CLOCKS_PER_SEC;

		timer = clock();

		words = createAnagram(n, k);

		for(auto it = words.begin(); it != words.end(); ++it)
		{
			sort(it->begin(), it->end());

			if(solutions.count(*it))
			{
				solutions.erase(*it);
				rejected.insert(pair<string,int>(*it, 0));
			}
			else if(rejected.count(*it) == 0)
			{
				solutions.insert(pair<string,int>(*it, 0));
			}
		}

		totDuration = (clock() - timer) / (double) CLOCKS_PER_SEC;

		totDuration -= forloopDuration;

		printf("%d\t%f\t%f\n", n, totDuration, prevTime);

		prevTime = totDuration;
	}

	return 0;
}


vector<string> createAnagram(int n, int k)
{
	string word;
	vector<string> vec;

	for(int i = 0; i < n; i++)
	{
		word = "";

		for(int j = 0; j < k; j++)
		{
			word += rand() % 26 + 97;
		}
		vec.push_back(word);
	}

	return vec;
}



