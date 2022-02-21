#include <bits/stdc++.h>

#define eb emplace_back
#define fi first
#define se second
#define in read<int>()
#define rep(i, x, y) for(int i = (x); i <= (y); i++)
#define per(i, x, y) for(int i = (x); i >= (y); i--)
using namespace std;

using pii = pair < int, int >;
using vec = vector < int >;
using veg = vector < pii >;

const int N = 1e5 + 10;

template < typename T > T read() {
	T x = 0; bool f = 0; char ch = getchar();
	while(!isdigit(ch)) f |= ch == '-', ch = getchar();
	while(isdigit(ch)) x = x * 10 + (ch ^ 48), ch = getchar();
	return f ? -x : x;
}

template < typename T > void chkmax(T &x, T y) { x = x < y ? y : x; }

int f[N], fa[N], go[N], n, ans[N];
vec G[N], pot[N];

int query(int x) {
	cout << "? " << x << endl;
	int v; cin >> v; return v;
}

void dfs(int x, int p) {
	fa[x] = p; go[x] = 0; f[x] = 1; pot[x].clear();
	for(auto y : G[x]) if(y ^ p) dfs(y, x), pot[x].eb(y);
	if(!pot[x].size()) return go[x] = x, void();
	sort(pot[x].begin(), pot[x].end(), [&](int a, int b) { return f[a] > f[b]; });
	go[x] = go[pot[x][0]]; rep(i, 0, pot[x].size() - 1) chkmax(f[x], f[pot[x][i]] + i);
	chkmax(f[x], (int)pot[x].size());
}

int g[N], pmx[N], smx[N];

int calcans(int x) {
	int res = 0;
	rep(i, 1, pot[x].size() - 1) chkmax(res, f[pot[x][i]] + i - 1);
	res += f[pot[x][0]]; return res;
}

void rdfs(int x, int p) {
	pot[x].clear(); for(auto y : G[x]) pot[x].eb(y);
	sort(pot[x].begin(), pot[x].end(), [&](int a, int b) { return f[a] > f[b]; });
	ans[x] = calcans(x); pmx[0] = smx[pot[x].size() + 1] = 0;
	rep(i, 0, pot[x].size() - 1) pmx[i + 1] = max(pmx[i], f[pot[x][i]] + i);
	per(i, pot[x].size() - 1, 0) smx[i + 1] = max(smx[i + 2], f[pot[x][i]] + i - 1);
	rep(i, 0, pot[x].size() - 1) g[pot[x][i]] = max(pmx[i], smx[i + 2]);
	for(auto y : G[x]) if(y ^ p) {
			f[x] = max(1, max(g[y], (int)pot[x].size() - 1));
			rdfs(y, x); 
		}
}

int tquery(int x) {
	int ct = 0;
	for(auto v : pot[x]) if(v ^ fa[x]) {
		if(ct) {
			int t = query(go[v]);
			if(t ^ x) return tquery(t);
		} ct++;
	} return x;
}

pii solve(int x) {
	dfs(x, 0); int a = 0, b = 0;
	for(auto v : pot[x]) {
		int t = query(go[v]);
		if(t ^ x) (a ? b : a) = tquery(t);
		if(b) break;
	} if(!a) a = x; if(!b) b = x; return pii{ a, b };
}

void answer(pii a) { cout << "! " << a.fi << " " << a.se << endl; }

int main() {
	cin.tie(0); cout.tie(0); cin >> n; rep(i, 2, n) { int u, v; cin >> u >> v; G[u].eb(v), G[v].eb(u); }
	if(n == 1) return cout << 0 << endl, cout << "! " << 1 << " " << 1 << endl, 0;
	dfs(1, 0), rdfs(1, 0); int cans = 0; rep(i, 1, n) chkmax(cans, ans[i]);
	cout << cans << endl; answer(solve(in));
}
