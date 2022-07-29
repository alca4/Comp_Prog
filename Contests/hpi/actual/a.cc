#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

int N;
vector<int> temps(1000);

int main()
{
    cin >> N;
    for (int i = 0; i < N; i++) cin >> temps[i];

    sort(temps.begin(), temps.begin() + N);

    cout << temps[N - 2] - temps[1] << endl;
    return 0;
}