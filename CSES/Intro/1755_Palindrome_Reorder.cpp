/*
  ___
 (o,o)
<  .  >
--"-"---
Rowlet is orz
*/
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <set>
#include <map>
#include <deque>
#include <queue>
#include <stack>
#include <unordered_set>
#include <unordered_map>
#include <bitset>
#include <cstring>
#include <cassert>
using namespace std;

#define F first
#define S second
#define pb push_back
#define ll long long
#define ld long double
#define INF 1000000000ull
#define MOD 1000000007ull
#define all(x) (x).begin(), (x).end()
#define reset(x) memset(x, 0, sizeof(x))
#define print(a, x, y) {for (int i = x; i <= y; i++) cout << a[i] << " "; cout << endl;}

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

int read()
{
    int a;
    cin >> a;
    return a;
}

const int MAXN = 100010;
map<char, int> freq;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string str;
    cin >> str;
    for (int i = 0; i < str.length(); i++) freq[str[i]]++;

    char odd_char = '#';
    for (auto n : freq) 
        if (n.second % 2 == 1)
        {
            if (odd_char != '#') odd_char = '!';
            else odd_char = n.first;
        }

    if (odd_char == '!') cout << "NO SOLUTION" << endl;
    else
    {
        if (odd_char != '#') freq[odd_char]--;
        string ans = "";
        for (auto n : freq) 
            for (int i = 0; i < n.second / 2; i++)
                ans += n.first;
        string tmp = ans;
        reverse(all(tmp));
        if (odd_char != '#') ans += odd_char;
        ans += tmp;
        cout << ans << endl;
    }
    return 0;
}