#include <bits/stdc++.h>
using namespace std;

//  https://stackoverflow.com/questions/440133/how-do-i-create-a-random-alpha-numeric-string-in-c
void gen_string(int n) {
    static const char alphanum[] =
    // "0123456789"
    // "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz";
    string tmp_s;
    tmp_s.reserve(n);

    for (int i = 0; i < n; ++i) {
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    
    cout << tmp_s << endl;
}

void gen_palindrome(int n) {
    static const char alphanum[] =
    // "0123456789"
    // "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    // "abcdefghijklmnopqrstuvwxyz";
    "abcde";
    string tmp_s;
    tmp_s.reserve(n);

    for (int i = 0; i <= n / 2; ++i) {
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    for (int i = n / 2 + 1; i < n; i++) tmp_s += tmp_s[n - 1 - i];
    
    cout << tmp_s << endl;
}

void gen_permutation(int n) {
    vector<int> vec(n);
    for (int i = 0; i < n; i++) vec[i] = i + 1;

    random_device rd;
    mt19937 g(rd());
    shuffle(vec.begin(), vec.end(), g);

    for (int i = 0; i < n; i++) cout << vec[i] << " ";
    cout << endl;
}

int main() {
    freopen("tc.in", "w", stdout);

    int tcs = 10000;
    cout << tcs << endl;
    while (tcs--) {
        // int N = 20;
        // cout << N << endl;
        gen_palindrome(20);
    }
}