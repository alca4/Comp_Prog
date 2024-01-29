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
// #define cerr cout
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

const int MAXN = 200010;
int N, Q;
vector<int> vert;
vector<int> horiz;
vector<pll> vj[18];
vector<pll> hj[18];

void solve() {
    cin >> N >> Q;
    vert.pb(-1);
    horiz.pb(-1);
    for (int i = 1; i <= N; i++) {
        char c;
        int v;
        cin >> c >> v;
        if (c == 'V') vert.pb(v);
        else horiz.pb(v);
    }

    sort(vert.begin(), vert.end());
    sort(horiz.begin(), horiz.end());

    int V = vert.size();
    int last_e = V;
    int last_o = V;
    for (int j = 0; j < 18; j++) vj[j].resize(V);
    for (int i = V - 1; i >= 1; i--) {
        if (vert[i] % 2 != 0) {
            if (last_e < V) {
                vj[0][i].FF = last_e;
                vj[0][i].SS = vert[last_e] - vert[i];
            }
            else vj[0][i].SS = LINF;
            last_o = i;
        }
        if (vert[i] % 2 == 0) {
            if (last_o < V) {
                vj[0][i].FF = last_o;
                vj[0][i].SS = vert[last_o] - vert[i];
            }
            else vj[0][i].SS = LINF;
            last_e = i;
        }

        for (int j = 1; j < 18; j++) {
            vj[j][i].FF = vj[j - 1][vj[j - 1][i].FF].FF;
            vj[j][i].SS = vj[j - 1][vj[j - 1][i].FF].SS + vj[j - 1][i].SS;
        }

        // for (int j = 0; j < 18; j++) {
        //     cout << j << " in front of " << i << ": " << vj[j][i].FF << endl;
        // }
    }

    int H = horiz.size();
    last_e = H;
    last_o = H;
    for (int j = 0; j < 18; j++) hj[j].resize(H);
    for (int i = H - 1; i >= 1; i--) {
        if (horiz[i] % 2 != 0) {
            if (last_e < H) {
                hj[0][i].FF = last_e;
                hj[0][i].SS = horiz[last_e] - horiz[i];
            }
            else hj[0][i].SS = LINF;
            last_o = i;
        }
        if (horiz[i] % 2 == 0) {
            if (last_o < H) {
                hj[0][i].FF = last_o;
                hj[0][i].SS = horiz[last_o] - horiz[i];
            }
            else hj[0][i].SS = LINF;
            last_e = i;
        }

        for (int j = 1; j < 18; j++) {
            hj[j][i].FF = hj[j - 1][hj[j - 1][i].FF].FF;
            hj[j][i].SS = hj[j - 1][hj[j - 1][i].FF].SS + hj[j - 1][i].SS;
        }

        // for (int j = 0; j < 18; j++) {
        //     cout << j << " in front of " << i << ": " << hj[j][i].FF << endl;
        // }
    }

    while (Q--) {
        // cerr << "New Query" << endl;
        int x, y;
        ll c;
        cin >> x >> y >> c;
        int eo;
        if (binary_search(vert.begin(), vert.end(), x)) {
            // cerr << "on a vertical road" << endl;
            if (lower_bound(horiz.begin(), horiz.end(), y) != horiz.end()) {
                if (c < *lower_bound(horiz.begin(), horiz.end(), y) - y) {
                    cout << x << " " << y + c << endl;
                    continue;
                }
                c -= *lower_bound(horiz.begin(), horiz.end(), y) - y;
                eo = (*lower_bound(horiz.begin(), horiz.end(), y) - y) & 1;
            }
            else {
                cout << x << " " << y + c << endl;
                continue;
            }
        } 
        else {
            // cerr << "on a horizontal road" << endl;
            if (lower_bound(vert.begin(), vert.end(), x) != vert.end()) {
                if (c < *lower_bound(vert.begin(), vert.end(), x) - x) {
                    cout << x + c << " " << y << endl;
                    continue;
                }
                c -= *lower_bound(vert.begin(), vert.end(), x) - x;
                eo = (*lower_bound(vert.begin(), vert.end(), x) - x) & 1;
            }
            else {
                cout << x + c << " " << y << endl;
                continue;
            }
        }

        int xloc = distance(vert.begin(), lower_bound(vert.begin(), vert.end(), x));
        int yloc = distance(horiz.begin(), lower_bound(horiz.begin(), horiz.end(), y));

        // cerr << "first intersection is " << vert[xloc] << " " << horiz[yloc] << endl;

        for (int j = 17; j >= 0; j--) {
            if (vj[j][xloc].SS + hj[j][yloc].SS <= c) {
                c -= vj[j][xloc].SS + hj[j][yloc].SS;
                xloc = vj[j][xloc].FF;
                yloc = hj[j][yloc].FF;
                // cerr << "moving to intersection " << vert[xloc] << " " << horiz[yloc] 
                //      << " with remaining " << c << endl;
            }
        }

        // north is even

        if (eo) {
            // cerr << "moving east" << endl;
            if (vj[0][xloc].SS <= c) {
                c -= vj[0][xloc].SS;
                xloc = vj[0][xloc].FF;
                // cerr << "moving to intersection " << vert[xloc] << " " << horiz[yloc] 
                //      << " with remaining " << c << endl;
                cout << vert[xloc] << " " << horiz[yloc] + c << endl;
            }
            else cout << vert[xloc] + c << " " << horiz[yloc] << endl;
        }
        else {
            // cerr << "moving north with " << c << endl;
            if (hj[0][yloc].SS <= c) {
                c -= hj[0][yloc].SS;
                yloc = hj[0][yloc].FF;
                // cerr << "moving to intersection " << vert[xloc] << " " << horiz[yloc] 
                //      << " with remaining " << c << endl;
                cout << vert[xloc] + c << " " << horiz[yloc] << endl;
            }
            else cout << vert[xloc] << " " << horiz[yloc] + c << endl;
        }
    }
}

int main() {
    // freopen("tc.in", "r", stdin);
    // freopen("tc.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T;
    T = 1;
    // cin >> T;
    // T = "change";
    while (T--) solve();

    return 0;
} 