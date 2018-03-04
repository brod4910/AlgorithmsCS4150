#include <stdlib.h>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <queue>
#include <iomanip>
#include <stdio.h>
#include <cstdlib>

using namespace std;

class Corridor
{
	public:
	int end;
	double f;

	Corridor(int end, double f) : end(end), f(f)
	{

	}
};

class Intersection
{
	public:
	vector<Corridor*> edges;

	Intersection* prev = NULL;
	double factor = 0.0;
	int intersection;

	Intersection(int x, int y, double f) : intersection(x)
	{
		addEdge(y, f);
	}

	void addEdge(int end, double f)
	{
		Corridor *c = new Corridor(end, f);
		edges.push_back(c);
	}
};

typedef pair<double, Intersection*> iPair;
typedef pair<double, int> testPair;

class Binary_Heap
{
	vector<iPair> heap;

	void HeapDown(int i)
	{
		int leftChild = (i * 2) + 1;
		int rightChild = leftChild + 1;
		int biggest = i;

		if(leftChild < heap.size() && heap.at(leftChild).first > heap.at(biggest).first)
		{
			biggest = leftChild;
		}
		if(rightChild < heap.size() && heap.at(rightChild).first > heap.at(biggest).first)
		{
			biggest = rightChild;
		}

		if(biggest != i)
		{
			std::swap(heap.at(i), heap.at(biggest));
			// iPair tmp = heap.at(i);
			// heap.at(i) = heap.at(biggest);
			// heap.at(biggest) = tmp;
			HeapDown(biggest);
		}
	}

	void HeapUp(int i)
	{
		// int parent = (i - 1) / 2;

		for(int i = heap.size() - 1; i > 0; i = (i-1)/2)
		{
			if(heap.at(i).first > heap.at((i-1)/2).first)
			{
				std::swap(heap.at(i), heap.at((i-1)/2));
			}
			else
			{
				break;
			}
		}
	}

	public:

	Binary_Heap()
	{
	}

	int size()
	{
		return heap.size();
	}

	bool empty()
	{
		return heap.size() == 0;
	}

	iPair removeMax()
	{
		iPair max = heap[0];
		heap[0] = heap[heap.size() - 1];

		heap.pop_back();

		if(heap.size() > 0)
		{
			HeapDown(0);
		}

		return max;
	}

	iPair peekMax()
	{
		return heap[0];
	}

	void insert(iPair p)
	{
		heap.push_back(p);

		HeapUp(heap.size() - 1);
	}
};

struct Dungeon
{
	map<int, Intersection*> intersections;
	int end;
};

void do_Dijkstras(queue<Dungeon> &dungeons);
void findBestFactor(map<int, Intersection*> &intersections);
void Dijkstras(map<int, Intersection*> &intersections);
void insertAndAdd(map<int, Intersection*> &intersections, int x, int y, double f);
void DijkstrasTest(int n, vector<vector<testPair>> dungeon, vector<double> &toPrint);

int main()
{
	int n, m, x, y;
	double f;
	// queue<Dungeon> dungeons;
	vector<double> toPrint;

	cin >> n >> m;

	while(true)
	{
		// Dungeon dungeon;
		// dungeon.end = m - 1;

		vector<vector<testPair>> dungeon(n);

		for(int i = 0; i < m; i++)
		{
			cin >> x >> y >> f;
			
			// insertAndAdd(dungeon.intersections, x, y, f);
			dungeon[x].push_back(make_pair(f, y));
			dungeon[y].push_back(make_pair(f, x));
		}

		DijkstrasTest(n, dungeon, toPrint);

		cin >> n >> m;

		if(n == 0 && m == 0)
		{
			break;
		}
	}

	for(auto it : toPrint)
	{

		cout << fixed;
		cout.precision(4);
		cout << it << endl;
	}

	return 0;
}

void DijkstrasTest(int n, vector<vector<testPair>> dungeon, vector<double> &toPrint)
{
	vector<bool> visited(n, false);
	vector<double> distance(n, 0);
	priority_queue<testPair> pq;
	int currentI, intersection;
	double factor, intersecFactor;

	pq.push(make_pair(1, 0));

	while(!pq.empty())
	{
		factor = pq.top().first;
		currentI = pq.top().second;
		pq.pop();

		if(visited[currentI])
		{
			continue;
		}

		visited[currentI] = true;

		distance[currentI] = factor;

		for(auto it : dungeon[currentI])
		{
			intersecFactor = it.first;
			intersection = it.second;

			pq.push(make_pair(factor * intersecFactor, intersection));
		}
	}

	toPrint.push_back(distance[n-1]);
}

void insertAndAdd(map<int, Intersection*> &intersections, int x, int y, double f)
{
	if(intersections.find(x) != intersections.end())
	{
		intersections.find(x)->second->addEdge(y, f);
	}
	else if(intersections.find(x) == intersections.end())
	{
		Intersection *i = new Intersection(x, y, f);

		intersections.insert(make_pair(x, i));
	}

	if(intersections.find(y) != intersections.end())
	{
		intersections.find(y)->second->addEdge(x, f);
	}
	else if(intersections.find(y) == intersections.end())
	{
		Intersection *i = new Intersection(y, x, f);

		intersections.insert(make_pair(y, i));
	}
}

void do_Dijkstras(queue<Dungeon> &dungeons)
{
	Dungeon dungeon;

	while(!dungeons.empty())
	{
		dungeon = dungeons.front();
		dungeons.pop();

		Dijkstras(dungeon.intersections);

		cout << fixed;
		cout.precision(4);
		cout << dungeon.intersections.find(dungeon.end)->second->factor << endl;
	}
}

void Dijkstras(map<int, Intersection*> &intersections)
{
	// Binary_Heap bh(end);
	Binary_Heap bh;
	Intersection *u = intersections.find(0)->second, *v;
	double res;

	u->factor = 1.0;

	bh.insert(make_pair(u->factor, u));

	while(!bh.empty())
	{
		u = bh.removeMax().second;

		for(auto it : u->edges)
		{
			v = intersections.find(it->end)->second;
			res = u->factor * it->f;

			if(v->factor < res)
			{
				v->factor = res;
				bh.insert(make_pair(v->factor, v));
			}
		}
	}
}