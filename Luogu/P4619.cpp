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
const int mod = 1e9 + 7;

ll f[N], ans;
int A, B, C, L;
int pri[N], pnum, mu[N], cnt, deg[N], u[N], v[N], w[N], val[N];
bool vis[N];
vec G[N];
unordered_map < int, bool > hav[N];

void init(int l) {
	rep(i, 2, l) {
		if(!vis[i]) pri[++pnum] = i, mu[i] = -1;
		rep(j, 1, pnum) {
			if(pri[j] * i > l) break;
			vis[pri[j] * i] = true; mu[pri[j] * i] = -mu[i]; if(i % pri[j] == 0) { mu[pri[j] * i] = 0; break; }
		}
	} mu[1] = 1;
}

int get(int n) {
	ll res = 0;
	for(int l = 1, r; l <= n; l = r + 1) { r = n / (n / l); res += 1ll * n / l * (r - l + 1); }
	return res % mod;
}

void solve() {
	A = in, B = in, C = in; L = max({ A, B, C }); cnt = 0;
	rep(i, 1, L) hav[i].clear(), deg[i] = 0, G[i].clear();
	per(pcd, L, 1) {
		for(int i = pcd; i <= L; i += pcd) if(mu[i]) {
				for(int j = i; j <= 1ll * L * pcd / i; j += pcd) if(mu[j]) {
						if(!hav[i][j]) {
							++cnt; u[cnt] = i; v[cnt] = j; w[cnt] = i / pcd * j;
							hav[i][j] = true; deg[i]++; deg[j]++;
						}
				}
			}
	}
	rep(i, 1, cnt) {
		int &u = ::u[i], &v = ::v[i];
		if(deg[u] < deg[v] || (deg[u] == deg[v] && u < v)) swap(u, v);
		G[u].eb(i);
	}
	ans = 0;
	auto calc = [&](int a, int b, int c, int d1, int d2, int d3) {
					int res = mu[d1] * mu[d2] * mu[d3];
					auto tcalc = [&](int A, int B, int C) {
									 ans += f[A / a] * f[B / b] % mod * f[C / c] % mod * res % mod;
									 ans = (ans + mod) % mod;
								 };
					tcalc(A, B, C); if(d1 == d2 && d2 == d3) return;
					tcalc(B, C, A), tcalc(C, A, B); if(d1 == d2 || d2 == d3 || d3 == d1) return;
					tcalc(A, C, B); tcalc(B, A, C); tcalc(C, B, A);
				};
	rep(i, 1, L) {
		for(auto eid : G[i]) val[v[eid]] = w[eid];
		for(auto eid : G[i])
			for(auto eeid : G[v[eid]])
				if(val[v[eeid]]) calc(w[eid], w[eeid], val[v[eeid]], i, v[eid], v[eeid]);
		for(auto eid : G[i]) val[v[eid]] = 0;
	} printf("%lld\n", ans);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	rep(i, 1, 100000) f[i] = get(i);
	init(100000);
	for(int T = in; T; T--) solve();
	return 0;
}
