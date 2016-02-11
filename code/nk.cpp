#include <cstring>
#include <algorithm>
#include <cmath>
#include <queue>
#include <cassert>
#include <cstdio>
#include <map>
#include <vector>

using namespace std;

#define mp make_pair


int X, Y, D;
int DL, ML;
int P, W;
int C;

template<class T, class V> long long dist(T a, V b) {
  return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

struct Warehouse {
  int x, y;
  vector<int> cap;
  vector<int> f;
  Warehouse() {}

  void read() {
    scanf("%d%d", &x, &y);
    cap = vector<int>(P);
    for (int i = 0; i < P; i++) {
      scanf("%d", &cap[i]);
    }
  }
};

struct Customer {
  int x, y;
  map<int, int> cap;
  map<int, int> f;
  Customer() {}
  void read() {
    scanf("%d%d", &x, &y);
    int l_;
    scanf("%d", &l_);
    for (int i = 0; i < l_; i++) {
      int x;
      scanf("%d", &x);
      cap[x]++;
      assert(cap[x] <= 1);
    }
  }
};

struct Action {
  char t;
  int to, count, product;
  Action(char t, int to, int count, int product): t(t), to(to), count(count), product(product) {}
};

struct Drone {
  int x, y;
  int f;
  int id;
  int t;
  map<int, int> l;
  vector<Action> acts;

  Drone() {
  }

  Drone(int i, const Warehouse &w) {
    id = i;
    x = w.x;
    y = w.y;
    t = 0;
    f = 0;
  }

  void action(char t, int to, int count, int product) { 
    acts.push_back(Action(t, to, count, product));
  }
  
  void print() {
    for (size_t i = 0; i < acts.size(); i++) {
      Action act = acts[i];
      printf("%d %c %d %d %d\n", id, act.t, act.to, act.count, act.product);
    }
  }
};

vector<int> weight;
vector<Warehouse> wh;
vector<Customer> cust;
vector<Drone> dr;


int main() {
  scanf("%d%d", &X, &Y);
  scanf("%d", &D);
  scanf("%d%d", &DL, &ML);
  scanf("%d", &P);
  weight = vector<int>(P, 0);
  for (int i = 0; i < P; i++) {
    scanf("%d", &weight[i]);
  }
  scanf("%d", &W);
  wh = vector<Warehouse>(W);
  for (int i = 0; i < W; i++) {
    wh[i].read();
  }
  scanf("%d", &C);
  cust = vector<Customer>(C);
  for (int i = 0; i < C; i++) {
    cust[i].read();
  }
  dr = vector<Drone>(D);
  for (int i = 0; i < D; i++) {
    dr[i] = Drone(i, wh[0]);
  }
  vector<pair<long long, pair<int, int>>> ord;
  vector<int> intrest(C, 1);
  for (int i = 0; i < W; i++) {
    for (int j = 0; j < C; j++) {
      ord.push_back(mp(dist(wh[i], cust[j]), mp(i, j)));
    }
  }
  sort(ord.begin(), ord.end());
  priority_queue<pair<int, int>> pq;
  for (int i = 0; i < D; i++) {
    pq.push(mp(0, i));
  }
  for (auto x : ord) {
    int cid = x.second.second;
    int wid = x.second.first;
    int dd = ceil(sqrt(dist(wh[wid], cust[cid])));
  }
}
