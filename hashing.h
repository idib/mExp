#define _USE_MATH_DEFINES
#include <string>
#include <vector>
#include <math.h>
using namespace std;
struct note{
	string name;
	double value;
	int count;
	bool empty;
};

class hashing
{
public:
	string varIn(string e);
	string varIn(double e);
	bool empty(int e);
	bool var(string str,double e);
	bool var(int id, double e);
	bool varUp(int e);
	bool varDown(int e);
	bool reVar(string str, double e);
	bool reVar(int id, double e);
	int find(double e);
	int find(string e);
	double varOut(string e);
	hashing();
	hashing(int a);
	~hashing();
private:
	vector<note> notation;
	int count = 0;
};



hashing::hashing()
{
}

string hashing::varIn(string e)
{
	bool fl = true;
	int l = 0;
	int max = e.length();
	double value = 0;
	while (l < max && e[l] != '=') l++;
	if (l != max)
	{
		fl = false;
		value = atof(e.substr(l + 1, max - l - 1).c_str());
		e = e.substr(0, l);
	}
	int id = find(e);
	if (id > -1 & id < count)
	{
		notation[id].count++;
	}
	else{
		if (e == "pi")
		{
			id = notation.size();
			notation.resize(id + 1);
			notation[id].name = e;
			notation[id].count = 0;
			if (value == 0)
			{
				notation[id].value = M_PI;
			}
			else{
				notation[id].value = value;
			}
			notation[id].empty = false;
			count++;
			return '#' + to_string(id);
		}
		if (e == "e")
		{
			id = notation.size();
			notation.resize(id + 1);
			notation[id].name = e;
			notation[id].count = 0;
			if (value == 0)
			{
				notation[id].value = M_E;
			}
			else{
				notation[id].value = value;
			}
			notation[id].empty = false;
			count++;
			return '#' + to_string(id);
		}
		id = notation.size();
		notation.resize(id + 1);
		notation[id].name = e;
		notation[id].count = 0;
		notation[id].value = value;
		notation[id].empty = fl;
		count++;
	}
	return '#' + to_string(id);
}
string hashing::varIn(double e)
{
	int id = find(e);
	if (id > -1 & id < count)
	{
		notation[id].count++;
	}
	else{
		id = notation.size();
		notation.resize(id + 1);
		notation[id].name = " ";
		notation[id].count = 0;
		notation[id].value = e;
		count++;
	}
	return '#' + to_string(id);
}

bool hashing::empty(int e)
{
	if (e > -1 && e < notation.size())
		return notation[e].empty;
	return true;
}

bool hashing::var(string str, double e)
{
	int id = find(str);
	if (id > -1 & id < count)
	{
		notation[id].value = e;
		notation[id].empty = false;
		return true;
	}
	return false;
}

bool hashing::var(int str, double e)
{
	if (str < notation.size() && str > -1)
	{
		notation[str].value = e;
		notation[str].empty = false;
		return true;
	}
	return false;
}

bool hashing::reVar(string str, double e)
{
	int id = find(str);
	if (id > -1 & id < count)
	{
		notation[id].value += e;
		notation[id].empty = false;
		return true;
	}
	return false;
}


bool hashing::reVar(int str, double e)
{
	if (str < notation.size() && str > -1)
	{
		notation[str].value += e;
		notation[str].empty = false;
		return true;
	}
	return false;
}

bool hashing::varUp(int e)
{
	if (e < notation.size() && e > -1)
	{
		notation[e].value++;
		notation[e].empty = false;
		return true;
	}
	return false;
}

bool hashing::varDown(int e)
{
	if (e < notation.size() && e > -1)
	{
		notation[e].value--;
		notation[e].empty = false;
		return true;
	}
	return false;
}

int hashing::find(string e)
{
	for (int i = 0; i < count; i++)
	{
		if (notation[i].name == e)
			return i;
	}
	return -1;
}

int hashing::find(double e)
{
	for (int i = 0; i < count; i++)
	{
		if (notation[i].value == e)
			return i;
	}
	return -1;
}

double hashing::varOut(string e)
{
	if (e[0] == '#')
	{
		int id = atoi(e.substr(1).c_str());
		if (id > -1 & id < count)
		{
			return notation[id].value;
		}
		else{
			return 0;
		}
	}
	else{
		return atof(e.c_str());
	}
}

hashing::~hashing()
{
}