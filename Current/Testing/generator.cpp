#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;

int rand32() {
    return abs(rand() << 15 | rand());
}

int N = 1000000;
set<int> available;
vector<int> arr;

int main() {
    freopen("tc.in", "w", stdout);
    srand(time(NULL));
    cout << N << " " << N / 2 << endl;
    // for (int i = 1; i <= N; i++) arr.push_back(i);

    for (int i = 1; i < N; i++) {
        // // shuffle(arr.begin(), arr.end(), default_random_engine(i));
        // int ok = 1;
        // for (int j = 0; j < N; j++) if (j + 1 == arr[j]) {
        //     ok = 0;
        //     break;
        // }
        // if (ok) break;
        cout << i % 1000 + 1 + 1000 * (i / 1000) << " ";
    }

    cout << 1 << " ";
    cout << endl;
    return 0;
}