#include<iostream>
#include<fstream>
#include<vector>
#include<set>
#include<algorithm>
using namespace std;

int PRIME = 1000000007;
int N, M;
long spotty[500][501];
long plain[500][501];

long ConvToInt(char c)
{
    if (c == 'A') return 0;
    if (c == 'C') return 1;
    if (c == 'G') return 2;
    return 3;
}

int main()
{
    ifstream fin("cownomics.in");
    fin >> N >> M;
    for (int i = 0; i < N; i++) 
    {
        for (int j = 1; j <= M; j++)
        {
            char c;
            fin >> c;
            spotty[i][j] = ConvToInt(c);
        }
    }
    for (int i = 0; i < N; i++) 
    {
        for (int j = 1; j <= M; j++)
        {
            char c;
            fin >> c;
            plain[i][j] = ConvToInt(c);
        }
    }

    long factor = 1;
    for (int i = 0; i < N; i++)
    {
        plain[i][0] = 0;
        spotty[i][0] = 0;
        for (int j = 1; j <= M; j++)
        {
            plain[i][j] = (plain[i][j] * factor) % (PRIME) + plain[i][j - 1];
            spotty[i][j] = (spotty[i][j] * factor) % (PRIME) + plain[i][j - 1];
            factor *= 4;
            factor %= (PRIME);
        }
    }
    
    for (int i = 0; i < N; i++)
    {
        for (int j = 1; j <= M; j++)
            cout << plain[i][j] << " ";
        cout << endl;
        for (int j = 1; j <= M; j++)
            cout << spotty[i][j] << " ";
        cout << endl;
    }

    int min_len = M;
    for (int i = 1; i <= M; i++)
    {
        for (int j = i + 1; j <= M; j++) 
        {
            set<long> spot_cows;
            for (int h = 0; h < N; h++) 
                spot_cows.insert(spotty[h][j] - spotty[h][i - 1]);
            bool works = true;
            for (int h = 0; h < N; h++)
            {
                if (spot_cows.find(plain[h][i]) != spot_cows.end()) works = false;
            }
            if (works) min_len = min(min_len, j - i + 1);
        }
    }
    ofstream fout ("cownomics.out");
    fout << min_len << endl;
    return 0;
}