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

const int N = 2e5 + 10;
const int base = 19260817;
const int mod = 1e9 + 7;

ll hsh[N], pw[N], thsh[N], vhsh[N], pre[N], suf[N];
int n, siz[N], tsiz[N], psiz[N], ssiz[N];
vec G[N];

void dfs(int x, int p) {
	veg pot; siz[x] = 0;
	for(auto y : G[x]) if(y ^ p) {
			dfs(y, x); siz[x] += siz[y]; pot.eb(hsh[y], siz[y]);
		} sort(pot.begin(), pot.end());
	hsh[x] = '('; for(auto v : pot) hsh[x] = (hsh[x] * pw[v.se] + v.fi) % mod;
	hsh[x] = (hsh[x] * base + ')') % mod;
	siz[x] += 2; thsh[x] = hsh[x]; tsiz[x] = siz[x];
}

int stk[N], top;
vec alres;

void rdfs(int x, int p) {
	top = 0; for(auto y : G[x]) stk[++top] = y;
	sort(stk + 1, stk + top + 1, [](auto a, auto b) { return pii{ thsh[a], tsiz[a] } < pii{ thsh[b], tsiz[b] }; });
	pre[0] = '('; suf[top + 1] = ')'; psiz[0] = ssiz[top + 1] = 1;
	rep(i, 1, top) psiz[i] = psiz[i - 1] + tsiz[stk[i]];
	per(i, top, 1) ssiz[i] = ssiz[i + 1] + tsiz[stk[i]];
	rep(i, 1, top) pre[i] = (pre[i - 1] * pw[tsiz[stk[i]]] + thsh[stk[i]]) % mod;
	per(i, top, 1) suf[i] = (suf[i + 1] + pw[ssiz[i + 1]] * thsh[stk[i]]) % mod;
	if(G[x].size() < 4) {
		ll tot = '(';
		rep(i, 1, top) {
			int y = stk[i];
			tot = (tot * pw[tsiz[y]] + thsh[y]) % mod;
		} tot = (tot * base + ')') % mod; alres.eb(tot);
		//cerr << x << " " << tot << " " << hsh[x] << endl;
	}
	rep(i, 1, top) if(stk[i] ^ p) 
		vhsh[stk[i]] = (pre[i - 1] * pw[ssiz[i + 1]] + suf[i + 1]) % mod;
	for(auto y : G[x]) if(y ^ p) {
			thsh[x] = vhsh[y]; tsiz[x] = n * 2 - siz[y];
			rdfs(y, x);
		}
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in; rep(i, 2, n) { int u = in, v = in; G[u].eb(v), G[v].eb(u); }
	pw[0] = 1; rep(i, 1, n << 1) pw[i] = pw[i - 1] * base % mod;
	dfs(1, 0); rdfs(1, 0); sort(alres.begin(), alres.end());
	alres.resize(unique(alres.begin(), alres.end()) - alres.begin()); printf("%lu\n", alres.size());
	return 0;
}
