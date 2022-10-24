/*
Idea: string (hash)
Do some hashing to find locations of string
*/
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

#define f first
#define s second

typedef pair<int, int> pii;

int Q;
string master;
map<int, vector<int>> occ;
map<pii, int> mem;

int Hash(const string& str, int start, int end)
{
    int hash = 0;
    for (int i = start; i <= end; i++) 
        hash += pow(31, i - start) * str[i];
    return hash;
}

int main()
{
    cin >> master;
    int len = master.length();
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < len - i; j++) 
        {
            int hash = Hash(master, j, j + i);
            occ[hash].push_back(j);
        }
        
    cin >> Q;
    for (int i = 0; i < Q; i++)
    {
        string p1, p2;
        cin >> p1 >> p2;
        int v1 = Hash(p1, 0, p1.length() - 1);
        int v2 = Hash(p2, 0, p2.length() - 1);
        if (mem.find(pii(v1, v2)) != mem.end())
        {
            cout << mem[pii(v1, v2)] << endl;
            continue;
        }
        vector<int>& loc1 = occ[v1];
        vector<int>& loc2 = occ[v2];
        if (loc1.size() == 0 || loc2.size() == 0)
        {
            mem[pii(v1, v2)] = -1;
            mem[pii(v2, v1)] = -1;
            cout << -1 << endl;
            continue;
        }
        int ans = 1e9;
        int a = 0, b = 0;
        while (a < loc1.size() && b < loc2.size())
        {
            int temp_ans;
            int diff = abs(loc2[b] - loc1[a]);
            if (loc1[a] < loc2[b]) 
                temp_ans = max(diff + p2.length(), p1.length());
            else if (loc1[a] > loc2[b]) 
                temp_ans = max(diff + p1.length(), p2.length());
            else 
                temp_ans = max(p1.length(), p2.length());
            
            if (ans > temp_ans) ans = temp_ans;

            if (ans == 0) break;
            if (loc1[a] < loc2[b]) a++;
            else b++;
        }
        
        mem[pii(v1, v2)] = ans;
        mem[pii(v2, v1)] = ans;
        cout << ans << endl;
    }
    return 0;
}