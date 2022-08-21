#include<iostream>
#include<fstream>
#include<vector>
#include<map>
#include<deque>
#include<algorithm>
using namespace std;

int N;
deque<int> init_arr;
deque<int> sorted_arr;
map<int, deque<int>> positions;

void MoveForward(int& lp, int& active)
{
    while ((init_arr[lp] == -1 && lp < N) || 
           (!sorted_arr.empty() && init_arr[lp] == sorted_arr[0]))
    {
        while (lp < N && init_arr[lp] == -1) lp++;
        while (!sorted_arr.empty() && init_arr[lp] == sorted_arr[0])
        {
            init_arr[lp] = -1;
            active--;
            lp++;
            sorted_arr.pop_front();
        }
        if (lp >= N) break;
    }
    if (!sorted_arr.empty())
    {
        init_arr[positions[sorted_arr[0]][0]] = -1;
        positions[sorted_arr[0]].pop_front();
        active--;
        sorted_arr.pop_front();
    }
}

void MoveBack(int& up, int& active)
{
    while ((init_arr[up] == -1 && up >= 0) || 
           (!sorted_arr.empty() && init_arr[up] == sorted_arr[sorted_arr.size() - 1]))
    {
        while (up >= 0 && init_arr[up] == -1) up--;
        while (!sorted_arr.empty() && init_arr[up] == sorted_arr[sorted_arr.size() - 1])
        {
            init_arr[up] = -1;
            active--;
            up--;
            sorted_arr.pop_back();
        }
        if (up < 0) break;
    }
    if (!sorted_arr.empty())
    {
        init_arr[positions[sorted_arr[sorted_arr.size() - 1]][0]] = -1;
        positions[sorted_arr[sorted_arr.size() - 1]].pop_front();
        active--;
        sorted_arr.pop_back();
    }
}

int main()
{
    ifstream fin ("sort.in");
    fin >> N;
    init_arr.resize(N);
    sorted_arr.resize(N);
    for (int i = 0; i < N; i++) 
    {
        fin >> init_arr[i];
        sorted_arr[i] = init_arr[i];
        positions[init_arr[i]].push_back(i);
    }
    sort(sorted_arr.begin(), sorted_arr.end());

    int lp = 0;
    int up = N - 1;
    int active = N;
    int moo = 0;
    while (active > 0)
    {
        moo++;
        //cout << "moo" << endl;

        MoveBack(up, active);
        /*
        for (int i = 0; i < init_arr.size(); i++) cout << init_arr[i]; // second debug
        cout << endl;
        cout << "lower pointer is " << lp << endl;
        cout << "upper pointer is " << up << endl;
        cout << active << " are active " << endl;
        */
        if (active <= 0) break;

        MoveForward(lp, active);
        /*
        for (int i = 0; i < init_arr.size(); i++) cout << init_arr[i]; // fifth debug
        cout << endl;
        cout << "lower pointer is " << lp << endl;
        cout << "upper pointer is " << up << endl;
        cout << active << " are active " << endl;
        */
        if (active <= 0) break;

        /*
        for (int i = 0; i < init_arr.size(); i++) cout << init_arr[i]; // first debug
        cout << endl;
        cout << "lower pointer is " << lp << endl;
        cout << "upper pointer is " << up << endl;
        cout << active << " are active " << endl;
        */

    }
    ofstream fout ("sort.out");
    fout << moo << endl;
    return 0;
}