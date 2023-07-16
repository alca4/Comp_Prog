#include <iostream>
#include <chrono>
#include <set>
using namespace std;

typedef pair<int, int> pii;

int rand32() {
    return abs(rand() << 15 | rand());
}

int N = 200000;

int main() {
    // freopen("tc.out", "w", stdout);
    srand(time(NULL));
    cout << N << endl;
    for (int i = 1; i <= N; i++) cout << -1000000000 << " ";
    cout << endl;
    return 0;
}