#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>

typedef std::pair<int, int> person;

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);

    int N, T, c, t, total = 0;
    std::cin >> N >> T;

    std::vector<person> queue;
    std::vector<int> tot(T + 1, 0);

    for(int i = 0; i < N; i++)
    {
    	std::cin >> c >> t;

    	queue.push_back(std::make_pair(t, c));
    }

	for(int i = 0; i < queue.size(); i++)
	{
		person p = queue[i];

		for(int j = p.first; j >= 0; j--)
		{
			int curr = tot[j];

			if(p.second > curr)
			{
				tot[j] = p.second;
			}			

			p.second = std::min(p.second, curr); 
		}
	}

	for(auto it : tot)
	{
		total += it;
	}

    std::cout << total << std::endl;

    return 0;
}