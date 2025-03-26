/*
  ___
 (o,o)
<  .  >
--"-"---
Rowlet is orz
  _      _      _
>(.)__ >(.)__ >(.)__
 (___/  (___/  (___/
I am dum duck

Tooting Bec
*/
#include <bits/stdc++.h>
using namespace std;

#define FF first
#define SS second
#define pb push_back
#define ll long long
#define ld long double
#define ull unsigned ll
#define endl "\n"
#define EPS 1e-9
// #define cout cerr
ll INF = 1000000000;
ll LINF = 1000000000000000000;
ll MOD = 0;

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef complex<ld> cd;

ll add(const ll& a, const ll& b) {return (a + b) % MOD;}
ll sub(const ll& a, const ll& b) {return (a - b + MOD) % MOD;}
ll mult(const ll& a, const ll& b) {return (a * b) % MOD;}
ll power(ll a, ll b) {
    ll n = a;
    ll ans = 1;

    for (int i = 0; i < 32; i++) {
        if (b & 1) ans = (ans * n) % MOD;
        n = (n * n) % MOD;
        b >>= 1;
    }

    return ans;
}
ll divide(const ll& a, const ll& b) {return (a * power(b, MOD - 2)) % MOD;}
template<class X, class Y> void maxeq(X& x, Y y) {if (x < y) x = y;}
template<class X, class Y> void mineq(X& x, Y y) {if (x > y) x = y;}
template<class X, class Y> void addeq(X& x, Y y) {x = add(x, y);}
template<class X, class Y> void subeq(X& x, Y y) {x = sub(x, y);}
template<class X, class Y> void multeq(X& x, Y y) {x = mult(x, y);}
template<class X, class Y> void diveq(X& x, Y y) {x = divide(x, y);}

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MAXN = 100010;

struct ST {
    struct Node {
        ll sum = 0;
        ll minv = 0;
        ll maxv = 0;

        void merge(Node& b, Node& c) {
            sum = b.sum + c.sum;
            minv = min(b.minv, c.minv);
            maxv = max(b.maxv, c.maxv);
        }
    };
    vector<Node> seg;

    ST(int n) {
        seg.resize(n * 4 + 1);
    }

    void addToNode(int cid, ll v) {
        seg[cid].sum += v;
        seg[cid].minv += v;
        seg[cid].maxv += v;
    }

    void setNode(int cid, ll v) {
        seg[cid].sum = v;
        seg[cid].minv = v;
        seg[cid].maxv = v;
    }

    void set(int a, ll v, int cid, int ss, int se) {
        if (ss == se) {
            setNode(cid, v);
            return;
        }

        int mid = (ss + se) / 2;
        if (a <= mid) set(a, v, cid * 2, ss, mid);
        else set(a, v, cid * 2 + 1, mid + 1, se);
        seg[cid].merge(seg[cid * 2], seg[cid * 2 + 1]);
    }

    void update(int a, ll v, int cid, int ss, int se) {
        if (ss == se) {
            addToNode(cid, v);
            return;
        }

        int mid = (ss + se) / 2;
        if (a <= mid) update(a, v, cid * 2, ss, mid);
        else update(a, v, cid * 2 + 1, mid + 1, se);
        seg[cid].merge(seg[cid * 2], seg[cid * 2 + 1]);
    }

    int queryl(int cid, int ss, int se, int s, int target) {
        if (ss == se) return ss;
    
        int lcont = seg[cid * 2].sum;
    
        int mid = (ss + se) / 2;
        if (s + lcont < target) 
            return queryl(cid * 2 + 1, mid + 1, se, s + lcont, target);
        else 
            return queryl(cid * 2, ss, mid, s, target);
    }

    int queryr(int cid, int ss, int se, int s, int target) {
        if (ss == se) return ss;
    
        int rcont = seg[cid * 2 + 1].sum;
    
        int mid = (ss + se) / 2;
        if (s + rcont < target) 
            return queryr(cid * 2, ss, mid, s + rcont, target);
        else 
            return queryr(cid * 2 + 1, mid + 1, se, s, target);
    }
};

int N;
pii city[MAXN];
pii ccity[MAXN];

void reset_tc() {
    for (int i = 1; i <= N; i++) city[i] = ccity[i] = pii(0, 0);
}

void solve() {
    cin >> N;
    map<int, int> xcoords, ycoords;
    for (int i = 1; i <= N; i++) {
        cin >> city[i].FF >> city[i].SS;
        xcoords[city[i].FF] = 1;
        ycoords[city[i].SS] = 1;
    }
    int xc = 0;
    for (pii p : xcoords) xcoords[p.FF] = ++xc;
    int yc = 0;
    for (pii p : ycoords) ycoords[p.FF] = ++yc;
    for (int i = 1; i <= N; i++) ccity[i] = pii(xcoords[city[i].FF], ycoords[city[i].SS]);

    vector<int> xpts;
    for (pii p : xcoords) xpts.pb(p.FF);
    vector<int> ypts;
    for (pii p : ycoords) ypts.pb(p.FF);

    sort(city + 1, city + 1 + N);
    sort(ccity + 1, ccity + 1 + N);

    int bestans = 0;
    int x = 0, y = 0;

    int lb = 0;
    int ub = N;
    while (lb <= ub) {
        int mid = (lb + ub) / 2;
        // cout << "mid is: " << mid << endl;

        ST ycoordsl(N), ycoordsr(N);
        for (int i = 1; i <= N; i++) ycoordsr.update(ccity[i].SS, 1, 1, 1, N);

        int tx = 2 * INF, ty = 2 * INF;
        for (int i = 1; i <= N; i++) {
            int j = i + 1;
            while (j <= N && ccity[j].FF == ccity[i].FF) j++;
            j--;

            int l = max(ycoordsl.queryl(1, 1, N, 0, mid), ycoordsr.queryl(1, 1, N, 0, mid)) + 1;
            int r = min(ycoordsl.queryr(1, 1, N, 0, mid), ycoordsr.queryr(1, 1, N, 0, mid));

            // cout << l << " " << r << endl;

            if (r >= l) {
                tx = city[i].FF;
                ty = ypts[l - 1];
                // tx = i;
                // ty = l;
                // cout << "have ans " << tx << " " << ty << endl;
            }
    
            for (int k = i; k <= j; k++) {
                ycoordsl.update(ccity[k].SS, 1, 1, 1, N);
                ycoordsr.update(ccity[k].SS, -1, 1, 1, N);
            }
    
            i = j;
        }

        if (tx != 2 * INF && ty != 2 * INF) {
            bestans = mid;
            x = tx;
            y = ty;
            lb = mid + 1;
        }
        else ub = mid - 1;
    }

    cout << bestans << endl;
    cout << x << " " << y << endl;

    reset_tc();
}

int main() {
    // freopen("tc.in", "r", stdin);
    // freopen("tc.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T;
    // T = 1;
    cin >> T;
    // T = "change";
    while (T--) solve();

    return 0;
} 