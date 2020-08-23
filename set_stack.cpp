#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <set>
#include <map>
#include <algorithm>
using namespace std;

typedef set<int> iset;
map<iset, int> IDch;
vector<iset> setch;
vector<string> setstr;

#define ALL(x) x.begin(), x.end()
#define INS(x) inserter(x, x.begin())

void mkstr(const iset &x, string &s)
{
	string bef = "{";
	string aft = "}";
	s += bef;
	for(auto i : x){
		s += setstr[i];
		s += ",";
	}
	if(s[s.size() - 1] == ',')
		s[s.size() - 1] = '}';
	else
		s += aft;
	return;
}

int id(const iset &x)
{
	string s;
	if(IDch.count(x)) return IDch[x];
	setch.push_back(x);
	mkstr(x, s);
	setstr.push_back(s);
	return IDch[x] = setch.size() - 1;
}

void lookup(const stack<int> &stk)
{
	cout << setstr[stk.top()] << endl;
	return;
}

void command(stack<int> &stk)
{
	string cmd;
	while(cin >> cmd){
		if(cmd == "look") lookup(stk);
		else if(cmd == "push") stk.push(id(iset()));
		else if(cmd == "dup") stk.push(stk.top());
		else{
			if(stk.size() < 2){
				cout << "wrong, there are no two elements in the stack" << endl;
				continue;
			}
			auto s1 = setch[stk.top()]; stk.pop();
			auto s2 = setch[stk.top()]; stk.pop();
			iset s;
			if(cmd == "union")	
				set_union(ALL(s1), ALL(s2), INS(s));
			else if(cmd == "intersect")
				set_intersection(ALL(s1), ALL(s2), INS(s));
			else if(cmd == "add"){
				s = s2;
				s.insert(id(s1));
				}
			else{
				cout <<"invalid command" << endl;
				continue;
				}
			stk.push(id(s));
		}
		if(setch[stk.top()].size())
			cout << setch[stk.top()].size() << endl;
	}
}

int main()
{
	stack<int> stk;
	cout << "ready, you can start:" << endl; 
	command(stk);
	cout << "bYe" << endl;
	return 0;
}
