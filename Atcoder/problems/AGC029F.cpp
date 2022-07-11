#include <bits/stdc++.h>

#define in read()
#define fi first
#define se second
#define eb emplace_back
#define rep(i, x, y) for(int i = (x); i <= (y); i++)
#define per(i, x, y) for(int i = (x); i >= (y); i--)

using namespace std;

typedef long long ll;
typedef double db;
typedef vector < int > vec;
typedef pair < int , int > pii;

int read() {
    int x = 0; bool f = 0; char ch = getchar(); while(!isdigit(ch)) f |= ch == '-',ch = getchar();
    while(isdigit(ch)) x = x * 10 + (ch ^ 48),ch = getchar(); return f ? -x : x;
}


namespace F { // max_flow
	const int N = 2e5 + 10;
	const int M = 1e6 + 10;
    const int inf = 0x3f3f3f3f;
    int h[N], now[N], d[N], cnt = 1, S, T;
    struct edge { int v, w, nxt; } e[M << 1];
    inline void tlink(int x, int y, int w) { e[++cnt] = (edge) { y, w, h[x] }; h[x] = cnt; }
    inline void link(int x, int y, int w) { tlink(x, y, w); tlink(y, x, 0); }
    inline void setst(int s, int t) { S = s; T = t; }
    queue < int > q;
    bool bfs() {
		while(q.size()) q.pop(); q.push(S); memset(d, 0, sizeof d); d[S] = 1; now[S] = h[S];
		while(!q.empty()) {
			int x = q.front(); q.pop();
			for(int i = h[x], y; i; i = e[i].nxt)
				if(e[i].w && !d[y = e[i].v]) {
					d[y] = d[x] + 1; q.push(y); now[y] = h[y];
					if(y == T) return 1;
				}
		} return 0;
    }
    int dinic(int x, int flow) {
		if(x == T) return flow;
		int res = flow;
		for(int i = now[x], y; i && res; i = e[i].nxt) {
			now[x] = i;
			if(e[i].w && d[y = e[i].v] == d[x] + 1) {
				int k = dinic(y, min(res, e[i].w));
				if(!k) d[y] = 0; e[i].w -= k; e[i ^ 1].w += k; res -= k;
			}
		}
		return flow - res;
    }
    ll runit() {
		ll maxflow = 0,flow;
		while(bfs()) while(flow = dinic(S, inf)) maxflow += flow;
		return maxflow;
    }
}

const int N = 2e5 + 10;

int n;
vec pot[N];

int main() {
#ifdef YJR_2333_TEST
    freopen("1.in","r",stdin);
#endif
    n = in; F :: setst(0, n << 1);
	rep(i, 1, n - 1) {
		int x = in;
		while(x--) pot[i].eb(in);
		for(auto x : pot[i])
			F :: link(x, i + n, 1);
	}
	rep(x, 1, n) F :: link(0, x, 1);
	rep(x, n + 1, n + n - 1) F :: link(x, n << 1, 1);
	if(F :: runit() != n - 1) return puts("-1"), 0;
	int p = 0;
	return 0;
}
