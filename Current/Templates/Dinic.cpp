struct Edge {
    int d;
    ll flow;
    ll cap;
    int rev;
};

Edge edges[MAXN * 2];
vector<int> nbs[MAXN];

struct Dinic {
    int s_, t_;
    int level[MAXN];
    int next[MAXN];
    int rev = 1;

    int get_levels() {
        memset(level, 0, sizeof(level));

        queue<int> q;
        int start = (rev == 1 ? s_ : t_);
        q.push(start);
        level[start] = rev;
        int ok = 0;
        int end = (rev == 1 ? t_ : s_);

        while (!q.empty()) {
            int n = q.front();
            q.pop();
            // cerr << "bfs at " << n << endl;

            if (n == end) {
                ok = 1;
                break;
            }

            for (int i = 0; i < nbs[n].size(); i++) {
                Edge& e = edges[nbs[n][i]];

                if (e.flow < e.cap && level[e.d] == 0) {
                    level[e.d] = level[n] + rev;
                    q.push(e.d); 
                }
            }
        }

        return ok;
    }

    ll DFS(int n, int p, ll c) {
        if (n == t_) return c;
        
        for (; next[n] < nbs[n].size(); next[n]++) {
            Edge& e = edges[nbs[n][next[n]]];
            if (e.d == p) continue;
            
            if (e.flow < e.cap && level[e.d] == level[n] + rev) {
                // cout << "go to " << e.d << endl;
                ll v = DFS(e.d, n, min(c, e.cap - e.flow));

                if (v > 0) {
                    e.flow += v;
                    edges[e.rev].flow -= v;

                    return v;
                }
            }
        }

        return -1;
    }

    ll smax_flow() {
        ll flow = 0;

        while (get_levels()) {
            memset(next, 0, sizeof(next));
            ll v = DFS(s_, 0, LINF);
            while (v > 0) {
                flow += v;
                v = DFS(s_, 0, LINF);
            }
            rev *= -1;
        }

        return flow;
    }
};