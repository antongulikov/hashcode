#include <cstring>
#include <cstdio>
#include <map>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>

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

  for (int i = 0; i < q; i++) {
    int d;
    char c;
    scanf("%d %c", &d, &c);

    if (c == 'L' || 'U') {
      int nw, type, cnt;
      scanf("%d %d %d", &nw, &type, &cnt);
      int dist = dr[d].distToWh(wh[nw]);
      dr[d].t += dist + 1;
      if (c == 'L') {
        dr[d].l[type] += cnt;
        dr[d].f += cnt * weight[type];
        cerr << d << ' ' << type << ' ' << dr[d].l[type] << ' ' << cnt << endl;
        if (dr[d].f > ML) {
          cout << "Drone " << d << " overflow!" << endl;
          return 0;
        }
      }
    }

    if (c == 'D') {
      int cu, type, cnt;
      scanf("%d %d %d", &cu, &type, &cnt);
      int dist = dr[d].distToCust(cust[cu]);
      dr[d].t += dist + 1;
      int a = cust[cu].l[type];
      cust[cu].l[type] = a - cnt;
      if (cust[cu].l[type] < 0) {
         cout << "Some extra items of type " << type << " in customer " << cu << endl;
         cust[cu].l[type] = 0;
      }
      /* */
      if (cust[cu].l.empty()) {//customer is empty
        cerr << "delivered all" << endl;
        allscore += ceil((DL - dr[d].t) / DL * 100);
      }
    }

  }


  cout << "Total score: " << allscore << endl;

}
