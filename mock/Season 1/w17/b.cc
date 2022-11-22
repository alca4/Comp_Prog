#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <cmath>
using namespace std;

int T, N;
string str;

int test(int l)
{
    int i = 0;
    int b1 = 0;
    int b2 = 9;
    while (i < N)
    {
        if (l == 0 || str[i] == '0') return -1;
        else if (str[i] == '1')
        {
            if (i + l >= N) return -1;
            i++;
            for (int j = 0; j < l - 1; j++)
                if (str[i + j] != '0') return -1;
            i += l - 1;
            b1 = max(b1, str[i] - '0');
            i++;
        }
        else
        {
            if (i + l - 1 >= N) return -1;
            for (int j = 0; j < l - 1; j++)
                if (str[i + j] != '9') return -1;
            i += l - 1;
            b2 = min(b2, str[i] - '0');
            i++;
        }
    }
    return b1 + 10 - b2;
}

void solve()
{
    cin >> N >> str;
    int ans = 100000000;
    
    // Case 1
    for (int i = 1; i < N; i++)
    {
        if (N % i == 0)
        {
            set<string> distinct;
            for (int j = 0; j < N; j += i) distinct.insert(str.substr(j, i));
            string big = *distinct.rbegin();
            string small = *distinct.begin();
            if (small[0] == '0' && i != 1) continue;
            int diff = 0;
            for (int j = 0; j < i; j++)
            {
                diff *= 10;
                diff += ((big[j] - '0') - (small[j] - '0'));
                if (diff >= 10)
                {
                    diff = 100000000;
                    break;
                }
            }
            ans = min(ans, diff);
        }
    }
    
    // Case 2
    int oneloc = -1;
    for (int i = 0; i < N; i++)
        if (str[i] == '1') 
        {
            oneloc = i;
            break;
        }
    if (oneloc == -1)
    {
        cout << ans << endl;
        return;
    }

    int l = 0;
    for (int i = oneloc + 1; i < N; i++)
    {
        if (str[i] == '0') l++;
        else break;
    }

    int a1 = test(l);
    int a2 = test(l + 1);
    if (a1 != -1) ans = min(ans, a1);
    if (a2 != -1) ans = min(ans, a2);
    cout << ans << endl;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> T;
    while (T--) {solve();}
}