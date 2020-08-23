#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
using namespace std;

int min_step(int n)
{
	string s;
	string t;
	cin >> s;
	cin >> t;
	s = s + "0";
	t = t + "0";
	int minsteps = 0;
	int save = 0;
	int dif = 0;
	for(int i = 0, zs = 0, zt = 0; i < n + 1; i++){
		if(s[i] != t[i]){
			dif++;
			if(s[i] == '0'){
				zs++;
				save = (save < dif+zt+1-zs-(i+1)) ? dif+zt+1-zs-(i+1) : save;
			}
			else zt++;
		}
		else{
			if(i == n)
				save = (save < dif+zt-zs-n-2) ? dif+zt-zs-n-2 : save;
			else if(s[i] == '0'){
				zs++;
				save = (save < dif+zt-zs-(i+1)-1) ? dif+zt-zs-(i+1)-1 : save;
				zt++;
			}
			else continue;
		}
	}
	minsteps = dif - save;
	return minsteps;
}
int main()
{
	int k;
	vector<int> res;
	cin >> k;
	for(int i = 0; i < k; i++){
		int n = 0;
		cin >> n;
		res.push_back(min_step(n));
	}
	for(auto i : res)
		cout << i << endl;
	return 0;
}
