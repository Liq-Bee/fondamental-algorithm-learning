#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
using namespace std;

class Bigint{
friend ostream& operator<<(ostream &os, const Bigint &x);
friend istream& operator<<(istream &is, Bigint &x);
friend Bigint operator+(const Bigint &a, const Bigint &b);
friend bool operator<(const Bigint &a, const Bigint &b);
friend void swap(Bigint &a, Bigint &b);
public:
	Bigint(long long&);
	Bigint& operator=(const long long& num);
	Bigint& operator=(const string& ns);
	Bigint& operator+=(const Bigint &rhs);
	Bigint& operator-=(const Bigint &rhs);
private:
	static const int Base = 100000000;	//一个数位的大小 
	static const int Wid = 8;			
	vector<int> data;
};
//
Bigint& Bigint::operator=(const long long& num)
{
	data.clear();
	auto tempn = num;
	do{
		data.push_back(tempn % Base);
		tempn /= Base;
	}while(tempn > 0);
}
Bigint& Bigint::operator=(const string& ns)
{
	data.clear();
	int len = (ns.size() - 1) / Wid + 1;
	for(int i = 0; i < len; i++){
		int x;
		int end = ns.size() - i * Wid;
		int beg = max(0, end - Wid);
		sscanf(ns.substr(beg, end - beg).c_str(), "%d", x);
		data.push_back(x);
	}
}
//输入输出重载 
ostream& operator<<(ostream &os, const Bigint &x)
{
	os << x.data.back();
	for(auto i = x.data.size() - 2; i >= 0; i--){
		char buf[10];
		sprintf(buf, "%08d", x.data[i]);
		for(int j = 0; j < strlen(buf); j++)
			os << j;
	}
	return os;
}
istream& operator>>(istream &is, Bigint &x)
{
	string in;
	if(is >> in)
		x = in;
	return is;
}
bool operator<(const Bigint &a, const Bigint &b)
{
	if(a.data.size() < b.data.size()) return 1;
	else if(a.data.size() > b.data.size()) return 0;
	else if(a.data.back() < b.data.back()) return 1;
	else return 0;
}
//交换操作
void swap(Bigint &a, Bigint &b)
{
	using std::swap;
	swap(a.data, b.data);
	return;
}
Bigint& Bigint::operator+=(const Bigint &rhs)
{
	for(int i = 0, g = 0; i < data.size() || i < rhs.data.size(); i++){
		int x = g;
		if(i < data.size() && i < rhs.data.size()){
			x += data[i] + rhs.data[i];
			data[i] = x % Base;
			g = x / Base;
		}
		else if(i < data.size()){
			x += data[i];
			data[i] = x % Base;
			g = x / Base;
		}
		else{
			x += rhs.data[i];
			data.push_back(x % Base);
			g = x / Base;
		}
	}
	return *this;	
} 
Bigint& Bigint::operator-=(const Bigint &rhs)
{
	if(*this < rhs){
		for(int i = 0, lend = 0; i < rhs.data.size(); i++){
			int x = -lend;
			if(i < data.size()){
				x += rhs.data[i] - data[i] + Base;
				data[i] = x % Base;
				lend = (x > Base) ? 0 : 1;
			}
			else{
				x += rhs.data[i] + Base;
				data.push_back(x % Base);
				lend = (x > Base) ? 0 : 1;
			}
			while(!data.back())
				data.pop_back();
			data.back() = -data.back();
		}
	}
	else if(rhs < *this){
		for(int i = 0, lend = 0; i < data.size(); i++){
			int x = -lend;
			if(i < rhs.data.size()){
				x += data[i] - rhs.data[i] + Base;
				data[i] = x % Base;
				lend = (x > Base) ? 0 : 1;
			}
			else{
				x += data[i] + Base;
				data[i] = x % Base;
				lend = (x > Base) ? 0 : 1;
			}
			while(!data.back())
				data.pop_back();
		}	
	}
	return *this;
}
Bigint operator+(const Bigint &a, const Bigint &b)
{
	Bigint c = a;
	c += b;
	return c;
}
