#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;
 
int T, N;
string str;

int find(int minId, string small)
{
    for (int i = minId; i <= str.length() - small.length(); i++)
    {
        bool found = 1;
        for (int j = 0; j < small.length(); j++)
            if (str[i + j] != small[j]) found = 0;
        if (found) return i;
    }
    return -1;
}
 
void solve()
{
    cin >> N;
    cin >> str;

    if (find(0, "A") < 0 || find(0, "R") < 0 || find(0, "S") < 0)
    {
        cout << "Impossible" << endl;
        return;
    }

    // ARS
    if (find(0, "ARS") >= 0)
    {
        cout << 0 << endl;
        return;
    }
    
    // AR-S, A-RS, SRA, 
    if (find(find(0, "AR"), "S") >= 0 || 
        find(find(0, "A"), "RS") >= 0 ||
        find(find(0, "A"), "SR") >= 0 || 
        find(find(0, "RA"), "S") >= 0 ||
        find(0, "SRA") >= 0 ||
        find(0, "RAS") >= 0 ||
        find(0, "ASR") >= 0 ||
        find(0, "RAS") >= 0) 
    {
        cout << 1 << endl;
        return;
    }

    if (find(find(0, "R"), "AS") >= 0 ||
        find(find(0, "S"), "RA") >= 0 ||
        find(find(0, "AS"), "R") >= 0 ||
        find(find(0, "SR"), "A") >= 0 ||
        find(find(0, "RS"), "A") >= 0 ||
        find(find(0, "SR"), "A") >= 0 ||
        find(find(0, "R"), "SA") >= 0 ||
        find(find(0, "SA"), "R") >= 0 ||
        find(find(find(0, "A"), "R"), "S") >= 0 ||
        find(find(find(0, "A"), "S"), "R") >= 0 ||
        find(find(find(0, "R"), "A"), "S") >= 0 ||
        find(find(find(0, "R"), "S"), "A") >= 0 ||
        find(find(find(0, "S"), "A"), "R") >= 0 ||
        find(0, "RSA") >= 0 ||
        find(0, "SAR") >= 0) 
    {
        cout << 2 << endl;
        return;
    }

    cout << 3 << endl;
    return;

    // S-R-A
}
 
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
 
    cin >> T;
    while (T--) {solve();}
}