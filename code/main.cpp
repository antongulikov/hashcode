#include <bits/stdc++.h>


using namespace std;

int X, Y, D;
int DL, ML;
int P, W;
int C;

#define border sldjfsdlkfj

const long double border = 1000;

struct Warehouse;
struct Customer;
struct Drone;

vector<int> weight;
vector<Warehouse> wh;
vector<Customer> cust;
vector<Drone> dr;



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

    int get_one() {
        for (int i = 0; i < cap.size(); i++)
            if (cap[i] > 0)
                return i;
        return -1;
    }

    bool have(vector <int> &a) {
        bool ok = true;
        for (int i = 0; i < a.size(); i++) {
            cap[a[i]]--;
        }
        for (int i = 0; i < a.size(); i++)
            ok &= cap[a[i]] >= 0;
        for (int i = 0; i < a.size(); i++)
            cap[a[i]]++;
        return ok;
    }
};

struct Customer {
    int x, y;
    map<int, int> l;
    vector <int> tt;
    Customer() {}
    void read() {
        scanf("%d%d", &x, &y);
        int l_;
        tt.clear();
        scanf("%d", &l_);
        for (int i = 0; i < l_; i++) {
            int x;
            scanf("%d", &x);
            tt.push_back(x);
            l[x]++;
        }
        random_shuffle(tt.begin(), tt.end());
    }
};

struct Action {
    char t;
    int to, count, product;
};


inline long double point_dist(int x1, int y1, int x2, int y2) {
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

int dist(const Warehouse &warehouse) {
    vector < long double > di(cust.size(), 0);
    for (int i = 0; i < cust.size(); i++) {
        di[i] = point_dist(cust[i].x, cust[i].y, warehouse.x, warehouse.y);
    }
    sort(di.begin(), di.end());
    int ret = 0;
    for (int i = 0; i < di.size(); i++) {
        ret++;
        if (di[i] > border)
            return ret;
    }
    return ret;
}



struct Drone {
    int x, y;
    int f;
    int t;
    int free_time;
    int my_w;
    map<int, int> l;
    vector<Action> act;

    Drone() {
        free_time = 0;
    }

    Drone(const Warehouse &w) {
        x = w.x;
        y = w.y;
        my_w = 0;
        t = 0;
        f = 0;
        free_time = 0;
    }


    void action(char t, int to, int count, int product) {
        act.push_back(Action{t, to, count, product});
    }

    void send_to_cust(int id, vector<int> &a) {
        int pos = -1;
        if (wh[my_w].have(a))
            pos = my_w;
        if (pos == -1)
            for (int i = 0; i < wh.size(); i++) {
                if (wh[i].have(a)) {
                    pos = i;
                    break;
                }
            }
        if (pos == -1)
            return;
        Customer &cst = cust[id];
        int sum = 0;
        free_time += (int)(point_dist(x, y, wh[pos].x, wh[pos].y) + 0.5);
        for (int i = 0; i < a.size(); i++) {
            action('L', pos, a[i], 1);
            wh[pos].cap[a[i]]--;
            sum += weight[a[i]];
            l[a[i]]++;
        }

        for (int i = 0; i < a.size(); i++) {
            action('D', id, a[i], 1);
            l[a[i]]--;
        }

        x = cst.x;
        y = cst.y;

        free_time += (int)(point_dist(x, y, cust[id].x, cust[id].y) + 0.5) + a.size() * 2;

        assert(sum <= ML);
    }
};


void to_war(int dron, int id) {
    auto & ware = wh[id];
    auto & drn = dr[dron];
    /*int get_one = ware.get_one();
    if (get_one == -1)
        return;;
    int d = (int)(point_dist(ware.x, ware.y, drn.x, drn.y) + 0.5) + 2;
    drn.free_time += d;
    drn.x = ware.x;
    drn.y = ware.y;
    drn.my_w = id;
    drn.action('L', id, get_one, 1);
    drn.action('U', id, get_one, 1);
    */
    drn.my_w = id;
}

void divide() {
    vector < pair <int, int > > cnt;
    cnt.clear();
    for (int i = 0; i < wh.size(); i++) {
        cnt.push_back({dist(wh[i]), i});
    }
    long long all = 0;
    for (int i = 0; i < cnt.size(); i++) {
        all += cnt[i].first;
    }
    sort(cnt.begin(), cnt.end());
    reverse(cnt.begin(), cnt.end());
    vector <int> boys;
    boys.clear();
    for (int i = 0; i < wh.size(); i++) {
        boys.push_back(D * cnt[i].first / all);
    }
    int rest = D;
    for (int x : boys)
        rest -= x;
    boys[0] += rest;
    int cntq = 0;
    for (int i = 0; i < wh.size(); i++) {
        while (boys[i] > 0) {
            to_war(cntq, cnt[i].second);
            boys[i]--;
            cntq++;
        }
    }
}


vector <int> order;

void do_cust(int id) {
    auto & cs = cust[id];
    int mft = 0;
    for (int iter = 0; iter < 200; iter++){
        for (int i = 0; i < dr.size(); i++) {
            if (dr[i].free_time < dr[mft].free_time)
                mft = i;
        }
        vector <int> a;
        int rest = ML;
        a.clear();
        for (int i = 0; i < cs.tt.size(); i++) if (cs.tt[i] != -1){
            if (rest - weight[cs.tt[i]] >= 0) {
                rest -= weight[cs.tt[i]];
                a.push_back(cs.tt[i]);
                cs.tt[i] = -1;
            }
        }
        dr[mft].send_to_cust(id, a);
    }
}

long double func(int x) {
    long double ret = 1e9;
    auto & customer = cust[x];
    int pos = 0;
    for (int i = 0; i < wh.size(); i++) {
        long double di = point_dist(customer.x, customer.y, wh[i].x, wh[i].y);
        if (di < ret) {
            ret = di;
            pos = i;
        }
    }
    return ret;
}

bool cmp(int x, int y)
{
    return func(x) < func(y);
}


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
        dr[i] = Drone(wh[0]);
    }

    divide();
    order.clear();

    for (int i = 0; i < C; i++)
        order.push_back(i);

    sort(order.begin(), order.end(), cmp);

    for (int i = 0; i < order.size(); i++)
        do_cust(order[i]);

    int all = 0;

    for (int id = 0; id < D; id++) {
        auto act0 = dr[id].act;
        for (size_t i = 0; i < act0.size(); i++) {
            Action act = act0[i];
            all++;
            //printf("%d %c %d %d %d\n", id, act.t, act.to, act.count, act.product);
        }
    }

    cout << all << endl;

    for (int id = 0; id < D; id++) {
        auto act0 = dr[id].act;
        for (size_t i = 0; i < act0.size(); i++) {
            Action act = act0[i];
            printf("%d %c %d %d %d\n", id, act.t, act.to, act.count, act.product);
        }
    }

    return 0;
}
