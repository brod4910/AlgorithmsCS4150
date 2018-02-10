#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <string>
#include <map>
#include <list>
#include <cmath>
#include <stack>
#include <queue>
#include <limits>

using namespace std;

class Edge
{
	string dest;
	// cost is to get from the to the new city.
	int cost;

	public:

	Edge(string dest, int cost) : dest(dest), cost(cost)
	{
	}

	string getDestination()
	{
		return dest;
	}

	int getCost()
	{
		return cost;
	}
};

class Vertex
{
	string city;
	// toll is the entrance into the city
	int toll;

	public:
	list<Edge> edges;
	// min cost is the minimum toll requirement to get from city a to b
	double minCost = numeric_limits<double>::infinity();
	
	Vertex(string city, int toll) : city(city), toll(toll)
	{
	}

	int getToll()
	{
		return toll;
	}

	string getCity()
	{
		return city;
	}
};

struct Trip
{
	string start;
	string dest;
};

// forward declarations for functions
void calculateTrips(map<string, Vertex*> cities, queue<Trip> &trips, int n);
void shortestPath(Vertex* start, stack<Vertex*> topSorted, map<string, Vertex*> cities);
stack<Vertex*> topologicalSortHelper(map<string, Vertex*> cities);
void topologicalSort(stack<Vertex*> &topSorted, map<string, Vertex*> &visited, map<string, Vertex*> &cities, Vertex* v);
void resetMinVals(map<string, Vertex*> cities);

int main()
{
	string buffer, cityName, highway, start, dest;
	char sizes[2048];
	int n, h, t, toll;
	map<string, Vertex*> cities;
	map<string, Vertex*>::iterator it;
	queue<Trip> trips;

	cin.getline(sizes, 2048);

	buffer = string(sizes);

	n = stoi(buffer.substr(0, buffer.length()));

	// get all the cities and put them into vertices
	for(int i = 0; i < n; i++)
	{
		getline(cin, buffer);

		cityName = buffer.substr(0, buffer.find(" "));
		toll = stoi(buffer.substr(buffer.find(" "), buffer.length()));

		Vertex *v = new Vertex(cityName, toll);

		cities.insert(make_pair(cityName, v));
	}

	cin.getline(sizes, 2048);

	buffer = string(sizes);

	h = stoi(buffer.substr(0, buffer.length()));

	for(int i = 0; i < h; i++)
	{
		getline(cin, buffer);

		cityName = buffer.substr(0, buffer.find(" "));
		highway = buffer.substr(buffer.find(" ") + 1, buffer.length());

		it = cities.find(highway);

		if(it != cities.end())
		{
			// get the toll requirement to get into the next city
			Edge e(highway, it->second->getToll());

			// push the edge into the source town edges
			cities.find(cityName)->second->edges.push_back(e);			
		}
	}

	cin.getline(sizes, 2048);

	buffer = string(sizes);

	t = stoi(buffer.substr(0, buffer.length()));

	// create the desired trips
	for(int i = 0; i < t; i++)
	{
		getline(cin, buffer);

		Trip trip;
		trip.start = buffer.substr(0, buffer.find(" "));
		trip.dest = buffer.substr(buffer.find(" ") + 1, buffer.length());

		trips.push(trip);
	}

	calculateTrips(cities, trips, n);

	for(auto it : cities)
	{
		delete it.second;
	}

}

void calculateTrips(map<string, Vertex*> cities, queue<Trip> &trips, int n)
{
	Trip trip;

	// topologically sort the graph before anything
	stack<Vertex*> topSorted = topologicalSortHelper(cities);

	while(trips.size() != 0)
	{
		trip = trips.front();

		if(trip.start == trip.dest)
		{
			cout << 0 << endl;
			trips.pop();
			continue;
		}

		// compute the shorest path for every vertex given the start
		shortestPath(cities.find(trip.start)->second, topSorted, cities);

		if(cities.find(trip.dest)->second->minCost == numeric_limits<double>::infinity())
		{
			cout << "NO" << endl;
		}
		else
		{
			cout << cities.find(trip.dest)->second->minCost << endl;			
		}

		// make sure to reset the minCost values every iteration
		resetMinVals(cities);

		trips.pop();
	}
}

void shortestPath(Vertex* start, stack<Vertex*> topSorted, map<string, Vertex*> cities)
{
	// set the start minCost = 0 to find it in the stack
	start->minCost = 0.0;

	while(topSorted.empty() == false)
	{
		Vertex *v = topSorted.top();
		topSorted.pop();

		// found the start in the stack
		if(v->minCost !=  numeric_limits<double>::infinity())
		{
			// for all edges in the vertex, iterate over all of them
			// and compare the cost of the destination with the 
			// cost of the edge + the vertex
			for(auto it = v->edges.begin(); it != v->edges.end(); ++it)
			{
				if(cities.find(it->getDestination())->second->minCost > (v->minCost + it->getCost()))
				{
					cities.find(it->getDestination())->second->minCost = v->minCost + it->getCost();
				}
			}
		}
	}
}

void resetMinVals(map<string, Vertex*> cities)
{
	for(auto it : cities)
	{
		it.second->minCost = numeric_limits<double>::infinity();
	}
}


stack<Vertex*> topologicalSortHelper(map<string, Vertex*> cities)
{
	stack<Vertex*> topSorted;
	map<string, Vertex*> visited;

	for(auto it : cities)
	{
		// if the city has not been visited then do a topological sort
		if(visited.find(it.first) == visited.end())
		{
			topologicalSort(topSorted, visited, cities, it.second);
		}
	}

	return topSorted;
}

void topologicalSort(stack<Vertex*> &topSorted, map<string, Vertex*> &visited, map<string, Vertex*> &cities, Vertex* v)
{
	// insert the city into visited
	visited.insert(make_pair(v->getCity(), v));

	// for all edges in the vertex
	for(auto &it : v->edges)
	{		
		// if the edge has not yet been visited then
		// do a recursive call on that vertex
		if(visited.find(it.getDestination()) == visited.end())
		{
			topologicalSort(topSorted, visited, cities, cities.find(it.getDestination())->second);
		}
	}

	// lastly, push the vertex to the stack
	topSorted.push(v);
}


