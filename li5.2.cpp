#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
using namespace std;
vector<vector<int> > pile;

void find_block(int fd, int &p, int &h)
{
	for(auto i = pile.size(); i > 0; i--)
		for(auto j = pile[i-1].size(); j > 0; j--)
			if(pile[i-1][j-1] == fd){
				p = i - 1, h = j - 1;
				return;
			}
	return;
		
}

void clear_above(const int p, const int h)
{
	for(int hi = h + 1; hi < pile[p].size(); hi++){
		pile[pile[p][hi]].push_back(pile[p][hi]);
	}
	pile[p].resize(h + 1);
	return;
}

void move_to(const int pa, const int ha, const int pb)
{
	for(int i = ha; i < pile[pa].size(); i++)
		pile[pb].push_back(pile[pa][i]);
	pile[pa].resize(ha);
	return;
}
void make_piles(int n)
{
	for(int i = 0; i < n; i++){
//		vector<int> tempv;
//		tempv.push_back(i);
		pile.push_back({i});
	}
	return;	
}

void display()
{
	for(int i = 0; i != pile.size(); i++){
		cout << "i : ";
		for(auto j : pile[i])
			cout <<	j << " ";
		cout << endl;
		}
	return;
}

int main()
{
	cout << "How many piles do you want? Now input a number:" << endl;
	int n = 0;
	cin >> n;
	cout << "ok" << endl;
	make_piles(n);
	string s1, s2;
	int a, b;
	cout << "Now give your command:" << endl;
	while(cin >> s1 >> a >> s2 >> b){
		int pa, ha;
		int pb, hb;
		if(a > n || b > n){
			printf("The block number must < %d", n);
			continue;
		}	
		find_block(a, pa ,ha);
		find_block(b, pb, hb);
		if(s1 == "move")
			clear_above(pa, ha);
		else if(s1 != "pile"){
			cout << "Sorry, your command is wrong!" << endl;
			continue;
		}
		if(s2 == "onto")
			clear_above(pb, hb);
		else if(s2 != "over"){
			cout << "Sorry, your command is wrong!" << endl;
			continue;
		}
		move_to(pa, ha, pb);
	}
	display();
	return 0;
}
