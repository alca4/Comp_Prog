
//misaka and elaina will carry me to master
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <utility>
#include <cassert>
#include <algorithm>
#include <vector>
#include <functional>
#include <numeric>
#include <set>
#include <array>
#include <queue>
#include <map>
#include <chrono>
#include <random>

#define ll long long
#define lb long double
#define sz(x) ((int)(x.size()))
#define all(x) x.begin(), x.end()
#define pb push_back
#define mp make_pair
#define kill(x, s) {if(x){ cout << s << "\n"; return ; }}

#ifndef LOCAL
#define cerr while(0) cerr
#endif

const lb eps = 1e-9;
const ll mod = 1e9 + 7, ll_max = 1e18;
//const ll mod = (1 << (23)) * 119 +1, ll_max = 1e18;
const int MX = 2e5 +10, int_max = 0x3f3f3f3f;

struct {
  template<class T>
  operator T() {
    T x; std::cin >> x; return x;
  }
} in;

using namespace std;

string OR(string a, string b){
	if(sz(a) < sz(b)) swap(a, b);
	string c(max(sz(a), sz(b)), '0');
	for(int i = 0; i<max(sz(a), sz(b)); i++){
		if(i < sz(b)){
			c[i] = max(a[i], b[i]);
		}else{
			c[i] = a[i];
		}
	}
	return c;
}

bool cmp(string a, string b){//returns 1 if GREATER
	if(sz(a) != sz(b)) return sz(a) > sz(b);
	for(int i = sz(a)-1; i>=0; i--){
		if(a[i] != b[i]) return a[i] > b[i];
	}
	return 0;
}

void solve(){
	int n = in;
	string s = in;
	reverse(all(s));
	while(sz(s) && s.back() == '0'){
		n--;
		s.pop_back();
	}
	kill(sz(s) == 0, "0");
	//locate the first 0
	int zero = n-1;
	while(zero >= 0 && s[zero] != '0'){
		zero--;
	}
	if(zero == 0){
		while(n--) cout << "1";
		cout << "\n";
		return ;
	}
	zero = n - 1 - zero;
	cerr << zero << "\n";
	string ans(n, '0');
	//for(int i = 0; i<n; i++) ans[i] = 0;
	for(int i = 0; i<=zero; i++){
		string rel;
		for(int j = i; j<n; j++){
			rel.pb(s[j]);
		}
		string tmp = OR(rel, s);
		if(cmp(tmp, ans)){
			ans = tmp;
		}
	}
	reverse(all(ans));
	cerr << sz(ans) << "\n";
	assert(sz(ans) == n);
	cout << ans << "\n";

}

signed main(){
    freopen("tc.in", "r", stdin);
    freopen("tc2.out", "w", stdout);
  cin.tie(0) -> sync_with_stdio(0);

  int T = 1;
  //cin >> T;
  for(int i = 1; i<=T; i++){
		solve();
	}
  return 0;
}