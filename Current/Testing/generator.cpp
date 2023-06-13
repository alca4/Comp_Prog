#include <iostream>
#include <chrono>
#include <set>
using namespace std;

typedef pair<int, int> pii;

int rand32() {
    return abs(rand() << 15 | rand());
}

int N = 100000;
int M = 100000;
set<pii> edges;

int main() {
    srand(time(NULL));
    cout << N << endl;
    for (int i = 1; i <= N; i++) cout << (rand32() % 2) << endl;
    for (int i = 2; i <= N; i++) {
        cout << (rand32() % (i - 1)) + 1 << endl;
    }
    return 0;
}