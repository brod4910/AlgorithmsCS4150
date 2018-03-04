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
			iPair tmp = heap.at(i);
			heap.at(i) = heap.at(biggest);
			heap.at(biggest) = tmp;
			HeapDown(biggest);
		}
	}

	void HeapUp(int i)
	{
		int parent = (i - 1) / 2;

		while(i > 0 && heap.at(i).first > heap.at(parent).first)
		{
			iPair tmp = heap.at(parent);
			heap.at(parent) = heap.at(i);
			heap.at(i) = tmp;
			i = parent;
			parent = (i - 1) / 2;
		}
	}

	public:

	Binary_Heap(int size)
	{
		// heap = vector<iPair>(size);
	}

	int size()
	{
		return heap.size();
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
void Dijkstras(map<int, Intersection*> &intersections, int end);
double round_nplaces(double value, int to);
void insertAndAdd(map<int, Intersection*> &intersections, int x, int y, double f);
vector<string> split(const char *str, char c = ' ');
void DijkstrasPQ(map<int, Intersection*> &intersections);

int main()
{
	int n, m, x, y;
	double f;
	queue<Dungeon> dungeons;

	cin >> n >> m;

	while(true)
	{
		Dungeon dungeon;
		dungeon.end = m - 1;

		for(int i = 0; i < m; i++)
		{
			cin >> x >> y >> f;
			
			insertAndAdd(dungeon.intersections, x, y, f);
		}

		dungeons.push(dungeon);

		cin >> n >> m;

		if(n == 0 && m == 0)
		{
			break;
		}
	}

	do_Dijkstras(dungeons);

	return 0;
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

		Dijkstras(dungeon.intersections, dungeon.end + 1);

		cout << fixed;
		cout.precision(4);
		cout << dungeon.intersections.find(dungeon.end)->second->factor << endl;
	}
}

void Dijkstras(map<int, Intersection*> &intersections, int end)
{
	Binary_Heap bh(end);
	Intersection *u = intersections.find(0)->second, *v;
	Corridor *c;
	iPair p;
	double res;

	u->factor = 1;

	bh.insert(make_pair(u->factor, u));

	while(bh.size() != 0)
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

double round_nplaces(double value, int to)
{
    double places = pow(10.0, to);
    return round(value * places) / places;
}