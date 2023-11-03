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

ll add(const ll& a, const ll& b) {
    ll x = a + b;
    if (a + b >= MOD) x -= MOD;
    return x;
}
ll sub(const ll& a, const ll& b) {
    ll x = a - b;
    if (a - b < 0) x += MOD;
    return x;
}
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

const int MAXN = 200010;
int N, M, K;
int arr[MAXN];
pii rngs[MAXN];
vector<pii> goodrngs;
vector<pii> bestrngs;
vector<int> bestvals;

struct ST {
    ll seg[4 * MAXN];

    void update(int a, int v, int cid, int ss, int se) {
        if (ss == se) {
            seg[cid] = v;
            return;
        }

        int mid = (ss + se) / 2;
        if (a <= mid) update(a, v, cid * 2, ss, mid);
        else update(a, v, cid * 2 + 1, mid + 1, se);
        seg[cid] = min(seg[cid * 2], seg[cid * 2 + 1]);
    }

    ll query(int a, int b, int cid, int ss, int se) {
        if (a <= ss && se <= b) return seg[cid];

        ll ans = INF;
        int mid = (ss + se) / 2;
        if (a <= mid) ans = min(ans, query(a, b, cid * 2, ss, mid));
        if (b > mid) ans = min(ans, query(a, b, cid * 2 + 1, mid + 1, se));
        return ans;
    } 

    void clear(int cid, int ss, int se) {
        seg[cid] = 0;
        if (ss == se) return;

        int mid = (ss + se) / 2;
        clear(cid * 2, ss, mid);
        clear(cid * 2 + 1, mid + 1, se);
    }
};

ST st;
int ones[MAXN], twos[MAXN];

bool Comp(const pii& p1, const pii& p2) {
    if (p1.FF == p2.FF) return p1.SS > p2.SS;
    return p1 < p2;
}

void solve() {
    // cout << "===== tc =====" << endl;
    cin >> N >> M >> K;
    for (int i = 1; i <= M; i++) {
        cin >> rngs[i].FF >> rngs[i].SS;
        arr[rngs[i].FF]++;
        arr[rngs[i].SS + 1]--;
    }

    for (int i = 1; i <= N; i++) arr[i] += arr[i - 1];
    for (int i = 1; i <= N; i++) {
        st.update(i, arr[i], 1, 1, N);
        ones[i] = ones[i - 1];
        twos[i] = twos[i - 1];
        if (arr[i] == 1) ones[i]++;
        if (arr[i] == 2) twos[i]++;
    }

    for (int i = 1; i <= M; i++) if (st.query(rngs[i].FF, rngs[i].SS, 1, 1, N) <= 2)
        goodrngs.pb(rngs[i]);
    
    sort(goodrngs.begin(), goodrngs.end(), Comp);

    int ans = 0;
    if (goodrngs.size()) {
        bestrngs.pb(goodrngs[0]);
        bestvals.pb(ones[goodrngs[0].SS] - ones[goodrngs[0].FF - 1]);
        for (int i = 1; i < goodrngs.size(); i++) {
            if (bestrngs.back().FF <= goodrngs[i].FF &&
                goodrngs[i].SS <= bestrngs.back().SS) {
                ans = max(ans, bestvals.back() + twos[goodrngs[i].SS] - twos[goodrngs[i].FF - 1]);
                // if (goodrngs[i] == bestrngs.back()) {
                //     bestrngs.pop_back();
                //     bestvals.pop_back();
                // }
            }
            else {
                bestrngs.pb(goodrngs[i]);
                bestvals.pb(ones[goodrngs[i].SS] - ones[goodrngs[i].FF - 1]);
            }
        }

        for (int i = 1; i < bestrngs.size(); i++) {
            ans = max(ans, bestvals[i - 1] + bestvals[i] + 
                           twos[bestrngs[i - 1].SS] - twos[bestrngs[i].FF - 1]);
        }

        multiset<int> baa;
        for (int i = 2; i < bestvals.size(); i++) baa.insert(bestvals[i]);

        for (int i = 0; i < (int) bestvals.size() - 2; i++) {
            ans = max(ans, bestvals[i] + *baa.rbegin());
            baa.erase(baa.find(bestvals[i + 2]));
        }

        for (int i = 0; i < (int) bestvals.size(); i++) ans = max(ans, bestvals[i]);
    }
    for (int i = 1; i <= N; i++) if (arr[i] == 0) ans++;
    cout << ans << endl;

    for (int i = 1; i <= N + 1; i++) arr[i] = ones[i] = twos[i] = 0;
    for (int i = 1; i <= M; i++) rngs[i].FF = rngs[i].SS = 0;
    goodrngs.clear();
    bestrngs.clear();
    bestvals.clear();
    st.clear(1, 1, N);
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