#include <cstring>
#include <vector>

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
  vector<int> l;
  Customer() {}
  void read() {
    scanf("%d%d", &x, &y);
    int l_;
    scanf("%d", &l_);
    l = vector<int>(l_);
    for (int i = 0; i < l_; i++) {
      scanf("%d", &l[i]);
    }
  }
};

struct Action {
  int t;
  Action() {}
};

struct Drone {
  int x, y;
  int f;
  int t;
  vector<int> l;
  vector<Action> act;

  Drone() {
  }

  Drone(const Warehouse &w) {
    x = w.x;
    y = w.y;
    t = 0;
    f = 0;
    l = vector<int>();
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
  for (int i = 0; i < W; i++) {
    wh[i].read();
  }
  scanf("%d", &C);
  for (int i = 0; i < C; i++) {
    cust[i].read();
  }
  dr = vector<Drone>(D);
  for (int i = 0; i < D; i++) {
    dr[i] = Drone(wh[0]);
  }
  vector<double, pair<int, int>> dist;
  for (int i = 0; i < W; i++) {
    for (int j = 0; j < C; j++) {
    }
  }
}
