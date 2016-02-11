#include <cstring>
#include <cstdio>
#include <map>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <cassert>

using namespace std;

int X, Y, D;
int DL, ML;
int P, W;
int C;

struct Warehouse {
  int x, y;
  vector<int> cap;
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
  map<int, int> l;
  Customer() {}
  void read() {
    scanf("%d%d", &x, &y);
    int l_;
    scanf("%d", &l_);
    for (int i = 0; i < l_; i++) {
      int x;
      scanf("%d", &x);
      l[x]++;
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
  int t;
  map<int, int> l;
  vector<Action> act;

  Drone() {
  }

  Drone(const Warehouse &w) {
    x = w.x;
    y = w.y;
    t = 0;
    f = 0;
  }

  void action(char t, int to, int count, int product) { 
    act.push_back(Action(t, to, count, product));
  }

  int distToWh(Warehouse w) {
    return ceil(sqrt((x - w.x) * (x - w.x) + (y - w.y) * (y - w.y)));
  }
  int distToCust(Customer c) {
    return ceil(sqrt((x - c.x) * (x - c.x) + (y - c.y) * (y - c.y)));
  }

};

vector<int> weight;
vector<Warehouse> wh;
vector<Customer> cust;
vector<Drone> dr;

int q;

int main() {
  freopen("sample.in", "r", stdin);
  cerr << "load data" << endl;
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
    dr[i] = Drone(wh[0]);
  }
  int allscore = 0;
  cerr << "finish read data " << endl;

  scanf("%d", &q);
  cerr << q << endl;
  cerr << cust[1].l[0] << endl;

  for (int i = 0; i < q; i++) {
    int d;
    char c;
    scanf("%d %c", &d, &c);
    assert(c == 'L' || c == 'U' || c == 'D');

    if (c == 'L' || c == 'U') {
      int nw, type, cnt;
      scanf("%d %d %d", &nw, &type, &cnt);
      int dist = dr[d].distToWh(wh[nw]);
      dr[d].t += dist + 1;
      if (c == 'L') {
        int a = dr[d].l[type];
        
        assert(type < P);
        
        dr[d].l[type] = a + cnt;
        dr[d].f += cnt * weight[type];
        
        
        if (dr[d].f > ML) {
          cout << "Drone " << d << " overflow! " << dr[d].f << endl;
          return 0;
        }
      }
    }

    if (c == 'D') {
      int cu, type, cnt;
      scanf("%d %d %d", &cu, &type, &cnt);
      int dist = dr[d].distToCust(cust[cu]);
      dr[d].t += dist + 1;
      dr[d].f -= cnt * weight[type];
      int a = cust[cu].l[type];
      cust[cu].l[type] = a - cnt;
      if (i == 8)
        cerr << a - cnt << ' ' << a << ' ' << cnt << ' ' << type << ' ' << cu << endl;
      if (a - cnt == 0) {
        cust[cu].l.erase(type);
      }
     
      if (cust[cu].l.empty()) {//customer is empty
        cerr << "delivered all customer " << cu << ", time " << dr[d].t << endl;
        allscore += ceil((DL - dr[d].t) * 1.0 / DL * 100);
      }
    }

  }


  cout << "Total score: " << allscore << endl;

}
