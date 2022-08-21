// long warning
#include<iostream>
#include<fstream>
#include<vector>
#include<cmath>
#include<climits>
#include<algorithm>
using namespace std;

struct Node
{
    string name;
    bool isFile = false;

    vector<int> nbs;
    int total_files;
    vector<int> files;

    long final_len;
};

int N;
int num_files = 0;
// 1-indexed
Node computer[100001];

int FindLeaves(int cur)
{
    vector<int>& nbs = computer[cur].nbs;
    if (computer[cur].isFile) return 1;
    int total_files = 0;
    for (int i = 0; i < nbs.size(); i++)
    {
        computer[cur].files[i] = FindLeaves(nbs[i]);
        total_files += computer[cur].files[i];
    }
    computer[cur].total_files = total_files;
    return total_files;
}

long FindTotalLen(int cur)
{
    //cout << "cur is: " << cur << endl;
    Node& here = computer[cur];
    if (here.isFile) return here.name.length();
    long ans = 0;
    for (int i = 0; i < here.nbs.size(); i++)
    {
        int a = FindTotalLen(here.nbs[i]);
        ans += a;
    }
    if (here.name != "bessie") ans += (here.name.length() + 1) * here.nbs.size();
    //cout << "adding " << here.name.length() + 1 << endl;
    //cout << "finished with " << cur << endl;
    return ans;
}

void FindOtherLens(int cur, int par)
{
    Node& here = computer[cur];
    Node& parent = computer[par];
    if (here.isFile) return;
    if (here.name != "bessie") 
    {
        here.final_len = parent.final_len - 
                         (here.total_files * (here.name.length() + 1)) +
                         3 * (num_files - here.total_files);
    }
    for (int i = 0; i < here.nbs.size(); i++) FindOtherLens(here.nbs[i], cur);
}

int main()
{
    ifstream fin ("dirtraverse.in");
    fin >> N;
    for (int i = 1; i <= N; i++)
    {
        fin >> computer[i].name;
        int m;
        fin >> m;
        if (m == 0)
        {
            computer[i].isFile = true;
            num_files++;
        }
        computer[i].nbs.resize(m);
        computer[i].files.resize(m);
        for (int j = 0; j < m; j++) fin >> computer[i].nbs[j];
    }
    
    computer[1].total_files = FindLeaves(1);
    computer[1].final_len = FindTotalLen(1);
    FindOtherLens(1, 0);

    long min_len = LONG_MAX;
    for (int i = 1; i <= N; i++)
    {
        if (!computer[i].isFile) 
        {
            min_len = min(min_len, computer[i].final_len);
            /*cout << "entity " << i << "'s len is " 
                 << computer[i].final_len << endl;*/
        }
    }

    ofstream fout ("dirtraverse.out");
    fout << min_len << endl;
    return 0;
}