#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <set>
using namespace std;
typedef long long ll;
ll ugly_num(const int &n)
{
	set<ll> ugnums;
	priority_queue<ll, vector<ll>, greater<ll>> prq;
	int ugn[3] = {2, 3, 5};
	ugnums.insert(1);
	
	for(auto i : ugn)
		prq.push(i);
		
	for(int i = 2; i <= n; i++){
		auto x = prq.top(); prq.pop();
//		cout << x << endl;
		if(i == n)
			return x;
		for(auto j : ugn){
			ll x2 = x * j;
			if(!ugnums.count(x2)){
				ugnums.insert(x2);
				prq.push(x2);}
		}
	}
}
int main()
{
	ll ngn = 0;
	int n;
	cout << "which ugly number do you want to know:" << endl;
	while(cin >> n){
		ngn = ugly_num(n);
		printf("the %dth ugly number is %lld \n", n, ngn);
	}
	return 0;
	
}
