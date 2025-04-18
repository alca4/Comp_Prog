/*
I hate this problem
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

const int MAXN = 200010;
int G, M;
ld t[MAXN];
struct Group
{
    vector<pii> students;
    ld avg;
} s[MAXN];
bool ans[MAXN];

int normal[MAXN], shiftdown[MAXN], shiftup[MAXN];
multiset<pair<ld, int>> avgs;

int main()
{
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T;
    cin >> T;
    while (T--)
    {
        cin >> M >> G;

        int N = 0;
        for (int i = 1; i <= M; i++) cin >> t[i];
        for (int i = 1; i <= G; i++)
        {
            int x;
            cin >> x;
            for (int j = 1; j <= x; j++)
            {
                int a;
                cin >> a;
                s[i].students.pb(pii(a, ++N));
                s[i].avg += a;
            }
            s[i].avg /= x;
        }

        sort(t + 1, t + 1 + M);
        sort(s + 1, s + 1 + G, [](const Group& g1, const Group& g2)
        {
            return g1.avg < g2.avg;
        });

        for (int i = 1; i <= G; i++) avgs.insert({s[i].avg, i});

        for (int i = M - G + 1; i <= M; i++) t[i - M + G] = t[i];

        for (int i = 1; i <= G; i++) 
        {
            normal[i] = normal[i - 1];
            if (s[i].avg > t[i]) normal[i]++;
        }
        for (int i = 2; i <= G; i++) 
        {
            shiftdown[i] = shiftdown[i - 1];
            if (s[i].avg > t[i - 1]) shiftdown[i]++;
        }
        for (int i = 1; i < G; i++) 
        {
            shiftup[i] = shiftup[i - 1];
            if (s[i].avg > t[i + 1]) shiftup[i]++;
        }

        for (int i = 1; i <= G; i++) for (int j = 0; j < s[i].students.size(); j++)
        {
            ld tmp = s[i].avg;
            avgs.erase(avgs.find({tmp, i}));
            ld avg2 = (s[i].avg * s[i].students.size() - s[i].students[j].FF) / 
                      (s[i].students.size() - 1);       

            auto n = avgs.lower_bound({avg2, -INF});
            int tar;
            if (n == avgs.end()) tar = G;
            else 
            {
                tar = n->SS;
                if (tar >= i) tar--;
            }

            // cout << "changing " << s[i].avg << " to " << avg2 << " target is: " << tar << endl;

            if (tar >= i)
                ans[s[i].students[j].SS] = ((1 <= i - 1 && normal[0] != normal[i - 1]) + 
                                            (tar + 1 <= G && normal[tar] != normal[G]) + 
                                            (i + 1 <= tar && shiftdown[i] != shiftdown[tar]) + 
                                            (avg2 > t[tar]) == 0);
            if (tar < i)
                ans[s[i].students[j].SS] = ((1 <= tar - 1 && normal[0] != normal[tar - 1]) + 
                                            (i + 1 <= G && normal[i] != normal[G]) + 
                                            (tar <= i - 1 && shiftup[tar - 1] != shiftup[i - 1]) + 
                                            (avg2 > t[tar]) == 0);
            avgs.insert({tmp, i});
        }

        for (int i = 1; i <= N; i++) 
        {
            cout << ans[i];
            ans[i] = 0;
        }
        cout << endl;

        for (int i = 1; i <= M; i++) t[i] = 0;
        for (int i = 1; i <= G; i++)
        {
            normal[i] = shiftdown[i] = shiftup[i] = 0;
            s[i].avg = 0;
            s[i].students.clear();
        }
        avgs.clear();
        // cout << endl;
    }
    
    return 0;
}