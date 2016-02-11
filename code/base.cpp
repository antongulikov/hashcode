
#include <bits/stdc++.h>

using namespace std;


typedef pair<int,int> pii;
#define pb push_back

const int MAXW = (int)1e4;

pii warehouses_init[MAXW];
vector<int> goods_init[MAXW];

pii orders[MAXW];
vector<int> want[MAXW];

vector<string> ans;


pii warehouses[MAXW];
vector<int> goods[MAXW];


struct drone
{
	static int capacity;
	int time, number;
	pii position;
	vector<int> type;
	drone () {}
	void wait(int w)
	{
		//
		time += w;
		
	}
	
	
};

int main() {
    return 0;
}
