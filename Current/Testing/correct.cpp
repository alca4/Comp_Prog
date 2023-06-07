#include <memory>
#include <iostream>
#include <algorithm>
#include <vector>
#include <chrono>
#include <climits>
#include <cassert>
#include <random>
using namespace std;

// #define int long long
#define problemname "treap"
#define pii pair<int,int>
#define vi vector<int>
#define pb push_back
#define ff first
#define ss second

bool ckmin(int& a, int b) {return a>b?a=b,true:false;}
bool ckmax(int& a, int b) {return a<b?a=b,true:false;}

const int MOD = 998244353;

const int MX = 2e5+5;
int tt=0;
int n;
vi a(MX);
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count()); // https://codeforces.com/blog/entry/61587
// node *root, *orig;
int root;
int root2;

struct treap{
    int timer=0;
    struct node {
        int ch[2];
        int v; long long sm; int sz;
    } tree[2800000];
    int newnode(int _v){
        tree[++timer].ch[0] = tree[timer].ch[1]=0;
        // assert(timer<2800000);
        tree[timer].v = _v;
        tree[timer].sm=_v;
        tree[timer].sz=1;
        return timer;
    }
    void dfs(int cur) {
        if(cur==0) return;
        dfs(tree[cur].ch[0]);
        a[tt++]=tree[cur].v;
        // assert(tt<=a.size());
        dfs(tree[cur].ch[1]);
    }
    int cnode(int _pos) {
        tree[++timer]=tree[_pos];
        assert(timer<2800000);
        return timer;
    }
    void pull(int t) {
        if(t==0) return;
        tree[t].sm = tree[t].v;
        tree[t].sz = 1;
        for(int dir : {0,1}) {
            tree[t].sm += (tree[tree[t].ch[dir]].sm);
            // tree[t].sm %= MOD;
            tree[t].sz += (tree[tree[t].ch[dir]].sz);
        }
    }
    void split(int t, int pos, int &l, int &r) {
        if(t==0) {l=r=0; return;}
        if(pos<=(tree[tree[t].ch[0]].sz)) {
            r = cnode(t);
            split(tree[t].ch[0], pos, l, tree[r].ch[0]);
            // r=t;
            pull(r);
        } else {
            l = cnode(t);
            split(tree[t].ch[1], pos-(tree[tree[t].ch[0]].sz)-1, tree[l].ch[1],r);
            pull(l);
        }
    }
    void merge(int &t, int l, int r) {
        if(l==0) {t=r; return;}
        if(r==0) {t=l; return;}
        if(rng()%(tree[l].sz+tree[r].sz) < tree[l].sz) { // no priority :)
        // if(1){
            t = cnode(l);
            merge(tree[t].ch[1], tree[l].ch[1], r);
        } else {
            t = cnode(r);
            merge(tree[t].ch[0], l, tree[r].ch[0]);
        }
        pull(t);
    }

    void build(int &t, int l, int r) {
        if(l>r) {t=0; return;}
        int m = (l+r)/2;
        t = newnode(a[m]);
        build(tree[t].ch[0],l,m-1);
        build(tree[t].ch[1], m+1, r);
        pull(t);
    }
    
    void reset() {
        // while(true){//dead
        // }
        tt=0;
        timer = tree[root2].sz;
        dfs(root);
        build(root, 0, n-1);
    }

    void ins(int pos, int val) {
        int l=0, r=0;
        split(root, pos, l, r);
        // cout<<l<<' '<<r<<endl;
        int nn = newnode(val);
        // cout<<nn<<endl;
        merge(l,l, nn);
        merge(root, l,r);
        // root = merge(l, merge(new node(val), r));
    }
    long long qry(int &t, int lpos, int rpos) {
        int l,m,r;
        split(t, rpos, l, r);
        split(l, lpos-1, l, m);
        long long ret=tree[m].sm;
        merge(l,l,m);
        merge(t,l,r);
        return ret;
    }
    void cpy(int lpos, int rpos, int k) {
        int l1,l2,r1,r2,m1,m2;
        split(root, lpos-1, l1, r1);
        split(l1, lpos-k-1, l1, m1);
        split(root, rpos, l2, r2);
        split(l2, lpos-1, l2, m2);
        while(tree[m1].sz<rpos-lpos+1){
            merge(m1,m1,m1);
        }
        split(m1,rpos-lpos+1, m1,m2);
        merge(l2,l2,m1); merge(root,l2,r2);
    }
    void revert(int orig, int lpos, int rpos) {
        // 0 4
        // node *rr=0, *mid=0;
        int l1,l2,r1,r2,m1,m2;
        split(root, rpos, l1, r1);
        split(l1, lpos-1, l1, m1);
        split(orig, rpos, l2, r2);
        split(l2, lpos-1, l2, m2);
        merge(l1, l1, m2);
        merge(root, l1, r1);
    }
    
};
treap tr;

int32_t main () {
    freopen("tc.in", "r", stdin);
    freopen("tc2.out", "w", stdout);
    ios_base::sync_with_stdio(0); cin.tie(0);
    int q;cin>>n>>q; 
    root=root2=0;
    // tr.ins(0,1);
    for(int i=1; i<=n; i++) {
        int x; cin>>x; a[i]=x;
        // tr.ins(i,x);
        // cout<<"ins "<<x<<endl;
    }
    tr.build(root2, 1, n);
    // cout<<tree[root2].sm<<endl;
    root=root2;
    // for(int i=0; i<n; i++) {
    //     tr.ins(i+n, a[i]);
    // }

    while(q--) {
        int t; cin>>t;
        if (t==1) {
            int l,r; cin>>l>>r;
            cout<<tr.qry(root,l,r)<<endl;
        } else if(t==2) {
            int l,r,k; cin>>l>>r>>k;
            // make copy!!
            tr.cpy(l,r,k);
        } else if (t==3) {
            int l, r; cin>>l>>r;
            // revert
            // cout<<"orig sum? "<<tree[root2].sm<<endl;
            tr.revert(root2, l,r);
        }
        if(tr.timer>1000000) {
            tr.reset();
        }
    }
    // return 0;
}


/*
5 7
1 2 3 4 5
1 1 5
2 3 4 1
1 1 5
2 3 4 2
1 1 5
3 1 5
1 1 5
*/