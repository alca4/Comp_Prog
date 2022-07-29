#include<iostream>
#include<fstream>
#include<algorithm>
#include<vector>
#include<set>
#include<map>
using namespace std;

int N;
map<int, int> first_occurence;
multiset<int> cows;

int main()
{
    ifstream fin ("circlecross.in");
    fin >> N;
    int pairs = 0;
    int num_complete = 0;
    for (int i = 1; i <= 2 * N; i++)
    {
        int cur;
        fin >> cur;
        if (cows.find(cur) == cows.end())
        {
            pairs += cows.size() - num_complete;
            cows.insert(cur);
            first_occurence[cur] = i;
        }
        else
        {
            cows.insert(cur);
            num_complete++;
        }
    }
    ofstream fout ("circlecross.out");
    fout << pairs / 2 << endl;
    return 0;
}