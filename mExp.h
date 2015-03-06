#define _USE_MATH_DEFINES
#include <math.h>
#include <string>
#include <vector>
#include "hashing.h"
using namespace std;


class mExp
{
public:
	string expression;
	double eps = 0.01;
	double value;
	mExp();
	mExp(string e);
	//mExp(string e, double eps);
	void overriden(string e);
	double calculate();
	double calculate(double x);
	~mExp();

private:
	string seq;
	string mexpression;
	hashing hashVar;
	vector <int> factint;
	double cal(string e,int depth);
	string hook(string e, char h);
	double seqCal(string e, int n = 0);
	string func(string type, string value);
	string delSpace(string e);
	int fact(int a);
	double degrees(double deg, double power);
};

mExp::mExp()
{
	expression = "";
}

mExp::mExp(string e)
{
	e = delSpace(e);
	int max = e.length();
	mexpression = "";
	string a;
	int i;
	for (i = 0; e[i] != ';' && i < max; i++)
	{
			 mexpression += e[i];
	}
	if (i + 1 != max)
	{
		for (int j = i + 1; j < max; j++)
		{
			if (e[j] == ',')
			{
				hashVar.varIn(a);
				a = "";
			}
			else{
				a += e[j];
			}
		}
		if (a != "")
		{
			hashVar.varIn(a);
		}
	}
	expression = e;
}



double mExp::calculate()
{
	value = cal(mexpression, 0);
	return value;
}

double mExp::cal(string e, int depth)
{
	int max = e.length();
	string a;
	if (depth < 1)
	{
		for (int i = 0; i < max; i++)
		{
			if (e[i] >= 'a' && e[i] <= 'z')
			{
				a = "";
				int start = i;
				while ((i < max) && (e[i] >= 'a' & e[i] <= 'z'))
				{
					a += e[i];
					i++;
				}
				if ((++i < max) && (e[i - 1] != '('))
				{
					string asfasf = e.substr(0, start);																		//test
					string asfasff = hashVar.varIn(a.c_str());																//test
					string asfasfff = e.substr(i - 1);																		//test
					e = e.substr(0, start) + hashVar.varIn(a.c_str()) + e.substr(i - 1);
					max = e.length();
				}
			}
		}
	}
	if (depth < 2)
	{
		for (int i = 0; i < max; i++)
		{
			if (e[i] >= 'a' && e[i] <= 'z')
			{
				a = "";
				int start = i;
				while ((i < max) && (e[i] >= 'a' & e[i] <= 'z'))
				{
					a += e[i];
					i++;
				}
				if ((++i < max) && (e[i - 1] == '('))
				{
					int startCel = i;
					int counts = 1;
					for (i; i < max & counts != 0; i++)
					{
						if (e[i] == '(')
							counts++;
						if (e[i] == ')')
							counts--;
					}
					string asfasf = e.substr(0, start);																		//test
					string asfasff = e.substr(startCel, i - startCel - 1);														//test
					string asfasfff = e.substr(i);
					e = e.substr(0, start) + func(a, e.substr(startCel, i - startCel - 1)) + e.substr(i);
					max = e.length();
				}
				else{
					string asfasf = e.substr(0, start);																		//test
					string asfasff = hashVar.varIn(a.c_str());																//test
					string asfasfff = e.substr(i-1);																		//test
					e = e.substr(0, start) + hashVar.varIn(a.c_str()) + e.substr(i - 1);
					max = e.length();
				}
			}
			else{
				if (e[i] == '(' || e[i] == '{' || e[i] == '<')
				{
					e = e.substr(0, i) + hook(e.substr(i + 1), e[i]);
					max = e.length();
				}
			}
		}
	}
	if (depth < 3)
	{
		a = "";
		for (int i = 0; i < max; i++)
		{
			if (e[i] == '+' || e[i] == '-')
			{
				if (e[i] == '+')
				{
					return cal(a, 2) + cal(e.substr(i + 1), 1);
				}
				else{
					if (!((i > -1) && ((e[i - 1] == '+') || (e[i - 1] == '*') || (e[i - 1] == '/') || (e[i - 1] == '-') || (e[i - 1] == '^'))))
					{
						return cal(a, 2) - cal(e.substr(i + 1), 1);
					}
				}
				a = "";
			}
			else{
				a += e[i];
			}
		}
	}
	if (depth < 4)
	{
		a = "";
		for (int i = 0; i < max; i++)
		{
			if (e[i] == '*' || e[i] == '/')
			{
				if (e[i] == '*')
				{
					return cal(a, 3) * cal(e.substr(i + 1),2);
				}
				else{
					return cal(a, 3) / cal(e.substr(i + 1), 2);
				}
				a = "";
			}
			else{
				a += e[i];
			}
		}
	}
	if (depth < 5)
	{
		for (int i = 0; i < max; i++)
		{
			if (e[i] == '!' || e[i] == '^')
			{
				if (e[i] == '!')
				{
					return fact(atoi(a.c_str()));
				}
				else{
					return degrees(atof(a.c_str()), atof(e.substr(i + 1).c_str()));
				}
			}
		}
	}
	return hashVar.varOut(e);
}



string mExp::hook(string e, char ch)
{
	int g;
	int max = e.length();
	int sc1 = 1, sc2 = 0, i = 0;
	char h2 = (ch == '(') ? ch + 1 : ch + 2;
	for (i; (i < max) & (sc1>sc2); i++)
	{
		if (e[i] == ch){
			sc1++;
		}
		if (e[i] == h2){
			sc2++;
		}
	}
	--i;
	return hashVar.varIn(cal(e.substr(0, i), 0)) + e.substr(i + 1);
}

string mExp::func(string type, string value)
{
	if (type == "sum")
	{
		int max = value.length();
		string a;
		vector <string> paramt;
		for (int i = 0; i < max; i++)
		{
			if (value[i] == ',' || value[i] == '\0')
			{
				paramt.push_back(a);
				a = "";
			}
			else{
				a += value[i];
			}
		}
		paramt.push_back(a);
		int n, iParams;
		double sum, x, x1;
		switch (paramt.size())
		{
		case 0:
			return 0;
			break;

		case 1:
			iParams = -99;
			for (int i = 0; i < max; i++)
			{
				if (value[i] == '#')
				{
					i++;
					int z = i;
					while (i < max && value[i] >= '0' && value[i] <= '9') i++;
					if (hashVar.empty(atoi(value.substr(z, i - z).c_str())))
					{
						iParams = atoi(value.substr(z, i - z).c_str());
						break;
					}
				}
			}
			if (iParams == -99)
			{
				return 0;
			}
			sum = 0;
			hashVar.varUp(iParams);
			x = cal(paramt[0], 1);
			hashVar.varUp(iParams);
			x1 = cal(paramt[0], 1);
			while (fabs(x)>eps & fabs(x) > fabs(x1)){
				sum += x;
				x = x1;
				hashVar.varUp(iParams);
				x1 = cal(paramt[0], 1);
			}
			return hashVar.varIn(sum);
			break;
		case 2:
			/*iParams = -99;
			int isParamsmax = -99;
			int maxs = paramt[0].length();
			max = paramt[0].length();
			for (int i = 0; i < max; i++)
			{
				if (paramt[0][i] == '#')
				{
					i++;
					int z = i;
					while (i < max && paramt[0][i] >= '0' && paramt[0][i] <= '9') i++;
					if (hashVar.empty(atoi(paramt[0].substr(z, i - z).c_str())))
					{
						iParams = atoi(paramt[0].substr(z, i - z).c_str());
						for (int i = 0; i < maxs; i++)
						{
						break;
					}
				}
			}
			
			if (iParams == -99)
			{
				return 0;
			}
			sum = 0;
			hashVar.varUp(iParams);
			x = cal(paramt[0], 1);
			hashVar.varUp(iParams);
			x1 = cal(paramt[0], 1);
			while (fabs(x)>eps & fabs(x) > fabs(x1)){
				sum += x;
				x = x1;
				hashVar.varUp(iParams);
				x1 = cal(paramt[0], 1);
			}
			return hashVar.varIn(sum);*/
			break;
		}
	}
	if (type == "sin"){
		return hashVar.varIn(sin(atof(value.c_str()) / 180 * M_PI));
	}
	if (type == "cos"){
		return hashVar.varIn(cos(atof(value.c_str()) / 180 * M_PI));
	}
	if (type == "tan"){
		return hashVar.varIn(tan(atof(value.c_str()) / 180 * M_PI));
	}
	if (type == "ctan"){
		return hashVar.varIn(1. / tan(atof(value.c_str()) / 180 * M_PI));
	}
	if (type == "arcsin"){
		return hashVar.varIn(asin(atof(value.c_str()) / M_PI * 180));
	}
	if (type == "arccos"){
		return hashVar.varIn(acos(atof(value.c_str()) / M_PI * 180));
	}
	if (type == "arctan"){
		return hashVar.varIn(atan(atof(value.c_str()) / M_PI * 180));
	}
	if (type == "arcctan"){
		return hashVar.varIn(atan(180. /( M_PI * atof(value.c_str()))));
	}
}

string mExp::delSpace(string e)
{
	int max = e.length();
	string a;
	for (int i = 0; i < max; i++)
	{
		if (e[i] != ' ')
			a += e[i];
	}
	return a;
}

int mExp::fact(int e)
{
	if (factint.empty()){
		factint.resize(1, 1);
	}
	else{
		if (factint.size() >= e){
			return factint[e];
		}
	}
	int max = factint.size() - 1;
	do{
		factint.resize(e + 1);
		max++;
		factint[max] = max*factint[max - 1];
	} while (max<e);
	return factint[e];
}

double mExp::degrees(double deg, double power)
{
	hashVar.varIn(exp(power * log(deg)));
}



mExp::~mExp()
{

}