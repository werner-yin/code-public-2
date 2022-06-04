#include <bits/stdc++.h>

#define eb emplace_back
#define ep emplace
#define fi first
#define se second
#define in read<int>()
#define lin read<ll>()
#define rep(i, x, y) for(int i = (x); i <= (y); i++)
#define per(i, x, y) for(int i = (x); i >= (y); i--)

using namespace std;

using ll = long long;
using db = double;
using pii = pair < int, int >;
using vec = vector < int >;
using veg = vector < pii >;

template < typename T > T read() {
	T x = 0; bool f = 0; char ch = getchar();
	while(!isdigit(ch)) f |= ch == '-', ch = getchar();
	while(isdigit(ch)) x = x * 10 + (ch ^ 48), ch = getchar();
	return f ? -x : x;
}

template < typename T > void chkmax(T &x, const T &y) { x = x > y ? x : y; }
template < typename T > void chkmin(T &x, const T &y) { x = x < y ? x : y; }

const int N = 1e6 + 10;

int n, m, a[N], b[N];
ll s[N];
vec G[N], rG[N];
int fa[N];

int gf(int x) { return fa[x] == x ? x : fa[x] = gf(fa[x]); }

queue < pii > q;

void upd(int x) {
	assert(s[x] == 0);
	for(auto v : G[x]) if(s[v - 1] == 0) q.ep(v, x);
	for(auto v : rG[x + 1]) if(s[v] == 0) q.ep(x + 1, v);
}

void solve() {
	n = in, m = in;
	rep(i, 1, n) a[i] = in;
	rep(i, 1, n) b[i] = in;
	rep(i, 0, n + 1) G[i].clear(), rG[i].clear();
	rep(i, 1, m) {
		int l = in, r = in;
		G[r].eb(l); rG[l].eb(r);
	}
	rep(i, 1, n) s[i] = s[i - 1] + b[i] - a[i];
	rep(i, 1, n + 1) fa[i] = i;
	while(q.size()) q.pop();
	rep(i, 1, n) if(s[i] == 0) upd(i);
	while(q.size()) {
		int x, y; tie(x, y) = q.front(); q.pop();
		for(int i = gf(x); i <= y; i = gf(i)) {
			s[i] = 0; upd(i); fa[i] = i + 1;
		}
	}
	bool fl = 1;
	rep(i, 1, n) fl &= s[i] == 0;
	puts(fl ? "YES" : "NO");
}

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	for(int T = in; T; T--) solve(); return 0;
}
