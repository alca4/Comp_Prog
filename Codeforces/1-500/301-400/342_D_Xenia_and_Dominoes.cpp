/*
Idea: bitmask dp
bitmask stores the tiling state of 2 rows
just be careful in your implementation
*/
#include <iostream>
#include <vector>
#include <bitset>
#include <map>
#include <cmath>
#include <algorithm>
using namespace std;

#define ll long long
#define MOD 1000000007

int N;
int game[4][10010];
int init[10010];
ll memo[10010][8][2];

int DP(int col, int fill, int valid)
{
    //cout << "calling " << col << " " << fill << " " << valid << endl;
    //cout << game[1][col] << " " << game[2][col] << " " << game[3][col] << endl;
    ll ans = 0;
    if (memo[col][fill][valid] != -1) 
    {
        //cout << "already seen before, had " << memo[col][fill][valid] << " ans" << endl;
        return memo[col][fill][valid];
    }   
    if (col <= N) 
    {
        if (fill == 0)
        {
            if (game[3][col] == 1) ans += DP(col, 3, 1);
            else ans = (ans + DP(col, 3, valid)) % MOD;
            if (game[1][col] == 1) ans += DP(col, 6, 1);
            else ans = (ans + DP(col, 6, valid)) % MOD;
            if (init[col + 1] == 0) 
            {
                if (game[1][col + 2] == 1 || game[1][col - 1] == 1 ||
                    game[2][col + 2] == 1 || game[2][col - 1] == 1 ||
                    game[3][col + 2] == 1 || game[3][col - 1] == 1)
                    ans = (ans + DP(col + 1, 7, 1)) % MOD;
                else
                    ans = (ans + DP(col + 1, 7, valid)) % MOD;
            }
        }
        if (fill == 1)
        {
            if (game[1][col] == 1) ans += DP(col, 7, 1);
            else ans = (ans + DP(col, 7, valid)) % MOD;
            if ((init[col + 1] | 2) != init[col + 1] && 
                (init[col + 1] | 4) != init[col + 1])
            {
                if (game[2][col + 2] == 1 || game[2][col - 1] == 1 ||
                    game[3][col + 2] == 1 || game[3][col - 1] == 1)
                    ans = (ans + DP(col + 1, init[col + 1] | 6, 1)) % MOD;
                else
                    ans = (ans + DP(col + 1, init[col + 1] | 6, valid)) % MOD;
            }
        }
        if (fill == 2)
        {
            if ((init[col + 1] | 1) != init[col + 1] && 
                (init[col + 1] | 4) != init[col + 1])
            {
                if (game[1][col + 2] == 1 || game[1][col - 1] == 1 ||
                    game[3][col + 2] == 1 || game[3][col - 1] == 1)
                {
                    ans = (ans + DP(col + 1, init[col + 1] | 5, 1)) % MOD;
                }
                else
                {
                    ans = (ans + DP(col + 1, init[col + 1] | 5, valid)) % MOD;
                }
            }
        }
        if (fill == 3)
        {
            if ((init[col + 1] | 4) != init[col + 1])
            {
                if (game[3][col + 2] == 1 || game[3][col - 1] == 1)
                {
                    ans = (ans + DP(col + 1, init[col + 1] | 4, 1)) % MOD;
                }
                else
                {
                    ans = (ans + DP(col + 1, init[col + 1] | 4, valid)) % MOD;
                }
            }
                
        }
        if (fill == 4)
        {
            if (game[3][col] == 1) ans += DP(col, 7, 1);
            else ans = (ans + DP(col, 7, valid)) % MOD;
            if ((init[col + 1] | 1) != init[col + 1] &&
                (init[col + 1] | 2) != init[col + 1])
            {
                if (game[2][col + 2] == 1 || game[2][col - 1] == 1 ||
                    game[1][col + 2] == 1 || game[1][col - 1] == 1)
                    ans = (ans + DP(col + 1, init[col + 1] | 3, 1)) % MOD;
                else
                    ans = (ans + DP(col + 1, init[col + 1] | 3, valid)) % MOD;
            }
        }
        if (fill == 5)
        {
            if ((init[col + 1] | 2) != init[col + 1])
            {
                if (game[2][col + 2] == 1 || game[2][col - 1] == 1)
                {
                    ans = (ans + DP(col + 1, init[col + 1] | 2, 1)) % MOD;
                }
                else
                {
                    ans = (ans + DP(col + 1, init[col + 1] | 2, valid)) % MOD;
                }
            }
                
        }
        if (fill == 6)
        {
            if ((init[col + 1] | 1) != init[col + 1])
            {
                if (game[1][col + 2] == 1 || game[1][col - 1] == 1)
                {
                    ans = (ans + DP(col + 1, init[col + 1] | 1, 1)) % MOD;
                }
                else
                {
                    ans = (ans + DP(col + 1, init[col + 1] | 1, valid)) % MOD;
                }
            }
                
        }
        if (fill == 7)
        {
            ans = (ans + DP(col + 1, init[col + 1], valid)) % MOD;
        }
    }
    //cout << "calculated " << col << " " << fill << " " << valid << endl;
    memo[col][fill][valid] = ans;
    return ans;
}

int main()
{
    cin >> N;
    for (int i = 1; i <= 3; i++)
    {
        for (int j = 1; j <= N; j++)
        {
            char c;
            cin >> c;
            if (c == '.') game[i][j] = 0;
            if (c == 'O') game[i][j] = 1;
            if (c == 'X') game[i][j] = 2;
        }
    }

    for (int j = 1; j <= N + 10; j++)
    {
        int r1 = (game[1][j] != 0);
        int r2 = (game[2][j] != 0) << 1;
        int r3 = (game[3][j] != 0) << 2;
        init[j] = r1 | r2 | r3;
    }

    for (int j = 1; j <= N; j++) 
        for (int i = 0; i <= 7; i++) 
            memo[j][i][0] = -1, memo[j][i][1] = -1;

    memo[N][7][1] = 1;
    memo[N][7][0] = 0;
    cout << DP(1, init[1], 0) << endl;
    return 0;
}