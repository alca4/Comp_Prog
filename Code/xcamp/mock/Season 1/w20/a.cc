#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

#define ll long long
#define P 1000000007

string str;
string vows = "aeiouAEIOU";
string cons = "qwrtypsdfghjklzxcvbnmQWRTYPSDFGHJKLZXCVBNM";
string all = "qwrtypsdfghjklzxcvbnmQWRTYPSDFGHJKLZXCVBNMaeiouAEIOU";
map<char, int> vid;
map<char, int> cid;
map<char, int> aid;
ll vc[100010][10][42];
ll cv[100010][42][10];
ll front[100010][52];
ll back[100010][52];

int isVowel(char c)
{
    return vows.find(c) != string::npos;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> str;
    for (int i = 0; i < vows.length(); i++) vid[vows[i]] = i;
    for (int i = 0; i < cons.length(); i++) cid[cons[i]] = i;
    for (int i = 0; i < all.length(); i++) aid[all[i]] = i;

    map<char, ll> pref;
    for (int i = 0; i < str.length(); i++)
    {
        if (i > 0) 
        {
            for (int j = 0; j < 10; j++)
                for (int k = 0; k < 42; k++)
                    vc[i][j][k] = vc[i - 1][j][k];
            for (int j = 0; j < 52; j++)
                front[i][j] = front[i - 1][j];
        }
        if (!isVowel(str[i]))
        {
            for (auto n : pref)
                if (n.second != 0) 
                {
                    vc[i][vid[n.first]][cid[str[i]]] += n.second;
                    vc[i][vid[n.first]][cid[str[i]]] %= P;
                    front[i][aid[n.first]] += n.second;
                    front[i][aid[n.first]] %= P;
                    front[i][aid[str[i]]] += n.second;
                    front[i][aid[str[i]]] %= P;
                }
        }
        else pref[str[i]]++;
    }

    map<char, ll> suff;
    for (int i = str.length() - 1; i >= 0; i--)
    {
        if (i < str.length() - 1) 
        {
            for (int j = 0; j < 42; j++)
                for (int k = 0; k < 10; k++)
                    cv[i][j][k] = cv[i + 1][j][k];
            for (int j = 0; j < 52; j++)
                back[i][j] = back[i + 1][j];
        }
        if (!isVowel(str[i]))
        {
            for (auto n : suff)
                if (n.second != 0) 
                {
                    cv[i][cid[str[i]]][vid[n.first]] += n.second;
                    cv[i][cid[str[i]]][vid[n.first]] %= P;
                    back[i][aid[str[i]]] += n.second;
                    back[i][aid[str[i]]] %= P;
                    back[i][aid[n.first]] += n.second;
                    back[i][aid[n.first]] %= P;
                }
        }
        else suff[str[i]]++;
    }

    /*
    for (int i = 0; i < str.length(); i++)
    {
        cout << i << endl;
        for (auto n : back[i])
        {
            cout << n.first << " has " << n.second << endl;
        }
    }
    */

    ll ans = 0;
    for (int i = 0; i < str.length(); i++)
    {
        if (isVowel(str[i]))
        {
            ll psum = 0;
            for (int j = 0; j < 10; j++)
                for (int k = 0; k < 42; k++)
                    psum += vc[i][j][k];
            psum %= P;
            ll ssum = 0;
            for (int j = 0; j < 42; j++)
                for (int k = 0; k < 10; k++)
                    ssum += cv[i][j][k];
            ssum %= P;
            ll a1 = (psum * ssum) % P;

            ll a2 = 0;
            // 1 = 3
            a2 += front[i][aid[str[i]]] * ssum;
            a2 %= P;

            // 3 = 5
            a2 += psum * back[i][aid[str[i]]];
            a2 %= P;

            // 1 = 5 or 2 = 4
            for (int j = 0; j < 52; j++)
                a2 += front[i][j] * back[i][j];
            a2 %= P;
            
            ll a3 = 0;
            // 1 = 3 and 2 = 4
            for (int j = 0; j < 10; j++)
                for (int k = 0; k < 42; k++)
                    if (j == vid[str[i]])
                    {
                        a3 += back[i][k] * vc[i][j][k];
                        a3 %= P;
                    }
            
            // 3 = 5 and 2 = 4
            for (int j = 0; j < 42; j++)
                for (int k = 0; k < 10; k++)
                    if (k == vid[str[i]])
                    {
                        a3 += front[i][j] * cv[i][j][k];
                        a3 %= P;
                    }
            
            // 1 = 5 and 2 = 4
            for (int j = 0; j < 10; j++)
                for (int k = 0; k < 42; k++)
                {
                    a3 += vc[i][j][k] * cv[i][k][j];
                    a3 %= P;
                }
            
            // 1 = 3 = 5
            a3 += front[i][aid[str[i]]] * back[i][aid[str[i]]] * 2;
            a3 %= P;

            ll a4 = 0;
            for (int j = 0; j < 10; j++)
                for (int k = 0; k < 42; k++)
                    if (j == vid[str[i]])
                    {
                        a4 += (vc[i][j][k] * cv[i][k][j]) * 2;
                        a4 %= P;
                    }
            a4 %= P;

            //cout << a1 << " " << a2 << " " << a3 << " " << a4 << endl;
            ans += (P + a1 - a2 + a3 - a4);
            ans %= P;
        }
    }

    cout << ans << endl;
    return 0;
}