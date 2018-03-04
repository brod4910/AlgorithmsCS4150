#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <cstdlib>
#include <string>
#include <map>
#include <queue>
#include <limits>
#include <algorithm>
#include <iostream>

using namespace std;

class Student
{
	public:
	string student;
	vector<Student*> friends;

	Student* prev = NULL;
	double distance = numeric_limits<double>::infinity();

	Student(string student) : student(student)
	{
	}

	void addFriend(Student* f)
	{
		friends.push_back(f);
	}
};

struct Rumor
{
	string start;
};

void createRumors(queue<Rumor> rumors, map<string, Student*> friends);
void resetGraph(const map<string, Student*> &friends);
void BFS(map<string, Student*> friends, Student* source);
void printTree(vector<Student*> printOrder);
vector<Student*> sortMap(map<string, Student*> &friends);

int main ()
{
	string buffer, student, friendName;
	char sizes[2048];
	int n, f, r;
	map<string, Student*> friends;
	queue<Rumor> rumors;

	cin.getline(sizes, 2048);

	buffer = string(sizes);

	n = stoi(buffer.substr(0, buffer.length()));

	// get all the friends and put them into vertices
	for(int i = 0; i < n; i++)
	{
		getline(cin, buffer);

		student = buffer.substr(0, buffer.length());

		Student *v = new Student(student);

		friends.insert(make_pair(student, v));
	}

	cin.getline(sizes, 2048);

	buffer = string(sizes);

	f = stoi(buffer.substr(0, buffer.length()));

	for(int i = 0; i < f; i++)
	{
		getline(cin, buffer);

		student = buffer.substr(0, buffer.find(" "));
		friendName = buffer.substr(buffer.find(" ") + 1, buffer.length());

		Student *s = friends.find(student)->second;
		Student *f = friends.find(friendName)->second;

		// add friends
		s->addFriend(f);
		f->addFriend(s);
	}

	cin.getline(sizes, 2048);

	buffer = string(sizes);

	r = stoi(buffer.substr(0, buffer.length()));

	// create the rumors
	for(int i = 0; i < r; i++)
	{
		getline(cin, buffer);

		Rumor rumor;
		rumor.start = buffer.substr(0, buffer.length());

		rumors.push(rumor);
	}

 	createRumors(rumors, friends);

	// for(auto it : friends)
	// {
	// 	delete it.second;
	// }

	return 0;
}

void createRumors(queue<Rumor> rumors, map<string, Student*> friends)
{
	vector<Student*> print;
	while(!rumors.empty())
	{
		Rumor r = rumors.front();
		rumors.pop();

		Student* source = friends.find(r.start)->second;

		BFS(friends, source);
		print = sortMap(friends);
		printTree(print);
		resetGraph(friends);
	}
}

void printTree(vector<Student*> printOrder)
{
	for(auto it = printOrder.begin(); it != printOrder.end(); ++it)
	{
		if(it == printOrder.begin())
		{
			cout << (*it)->student;
		}
		else
		{
			cout << " " << (*it)->student;
		}
	}

	cout << endl;
}

void resetGraph(const map<string, Student*> &friends)
{
	for(auto it : friends)
	{
		it.second->distance = numeric_limits<double>::infinity();
		it.second->prev = NULL;
	}
}

void BFS(map<string, Student*> friends, Student* source)
{

	queue<Student*> students;
	
	source->distance = 0;
	students.push(source);

	while(!students.empty())
	{
		Student* s = students.front();
		students.pop();

		for(auto it : s->friends)
		{
			if(it->distance == numeric_limits<double>::infinity())
			{
				students.push(it);
				it->distance = s->distance + 1;
				it->prev = s;
			}
		}
	}
}

vector<Student*> sortMap(map<string, Student*> &friends)
{
	vector<Student*> sorted;

	for(auto it : friends)
	{
		sorted.push_back(it.second);
	}

	stable_sort(sorted.begin(), sorted.end(), [](Student *s1, Student *s2){
		if(s1->distance == s2->distance)
		{
			if(s1->distance < s2->distance) return true;
			if(s1->distance > s2->distance) return false;
		}
		if(s1->distance < s2->distance) return true;
		if(s1->distance > s2->distance) return false;
		return false;
	});

	return sorted;
}