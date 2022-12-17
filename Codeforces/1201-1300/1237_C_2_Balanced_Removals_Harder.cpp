/*
  ___
 (o,o)
<  .  >
--"-"---
Rowlet is orz
  _      _      _
>(.)__ <(.)__ =(.)__
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
ll INF = 1000000000;
ll MOD = 1000000007;

ifstream fin(".in");
ofstream fout(".out");

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

ll add(const ll& a, const ll& b) {return (a + b) % MOD;}
ll sub(const ll& a, const ll& b) {return (a + MOD - b) % MOD;}
ll mult(const ll& a, const ll& b) {return (a * b) % MOD;}
ll power(ll a, ll b)
{
    ll n = b;
    ll ans = 1;

    ll binexp[64];
    binexp[0] = a;
    for (int i = 1; i < 64; i++) binexp[i] = mult(binexp[i - 1], binexp[i - 1]);

    while (n > 0)
    {
        int id = (int) log2(n & -n);
        ans = mult(ans, binexp[id]);
        n -= (n & -n);
    }

    return ans;
}
ll divide(const ll& a, const ll& b) {return (a * power(b, MOD - 2)) % MOD;}

int rand32()
{
    int a = rand();
    int b = rand();
    return (a << 16) | b;
}

ll rand64()
{
    ll a = rand32();
    ll b = rand32();
    return (a << 32) | b;
}

const int MAXN = 50010;
int N;

struct Pt
{
    ll x, y, z, id;
} points[MAXN];

int main()
{
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    for (int i = 1; i <= N; i++) 
    {
        cin >> points[i].x >> points[i].y >> points[i].z;
        points[i].id = i;
    }

    sort(points + 1, points + 1 + N, [](const Pt& p1, const Pt& p2) -> bool
    {
        return p1.x == p2.x ? (p1.y == p2.y ? p1.z < p2.z : p1.y < p2.y) : p1.x < p2.x;
    });

    int ops = 0;

    vector<Pt> pts;
    for (int i = 1; i <= N;)
    {
        int vx = points[i].x;
        int vy = points[i].y;
        vector<Pt> tmp;
        while (i <= N && points[i].x == vx && points[i].y == vy)
        {
            tmp.pb(points[i]);
            ++i;
            if (tmp.size() == 2) 
            {
                cout << tmp[0].id << " " << tmp[1].id << endl;
                tmp.pop_back();
                tmp.pop_back();
            }
        }

        if (tmp.size() == 1) pts.pb(tmp[0]);
    }

    vector<Pt> pts2;
    for (int i = 0; i < pts.size();)
    {
        int vx = pts[i].x;
        vector<Pt> tmp;
        while (i < pts.size() && pts[i].x == vx)
        {
            tmp.pb(pts[i]);
            ++i;
            if (tmp.size() == 2) 
            {
                cout << tmp[0].id << " " << tmp[1].id << endl;
                tmp.pop_back();
                tmp.pop_back();
            }
        }

        if (tmp.size() == 1) pts2.pb(tmp[0]);
    }

    for (int i = pts2.size() - 1; i >= 1; i -= 2)
        cout << pts2[i].id << " " << pts2[i - 1].id << endl;
    return 0;
} 