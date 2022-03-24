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
const int U = 262143;
const int mod = 1e9 + 7;

int n, a[N], f[U + 10], cnt[U + 10], lg[U + 10], phi[U + 10], pri[U + 10], pnum;
bool vis[U + 10];
ll qp(ll x, int t = mod - 2) { ll res = 1; for(; t; t >>= 1, x = x * x % mod) if(t & 1) res = res * x % mod; return res; }

void init(int l) {
	phi[1] = 1;
	rep(i, 2, l) {
		if(!vis[i]) pri[++pnum] = i, phi[i] = i - 1;
		rep(j, 1, pnum) {
			if(pri[j] * i > l) break; vis[pri[j] * i] = true; phi[pri[j] * i] = phi[i] * phi[pri[j]];
			if(i % pri[j] == 0) phi[pri[j] * i] = phi[i] * pri[j];
		}
	}
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in; rep(i, 1, n) a[i] = in, (a[i] && cnt[a[i]]++);
	f[0] = 1;
	rep(i, 2, U) lg[i] = lg[i >> 1] + 1;
	rep(s, 1, U) {
		int x = lg[s & -s];
		for(int t = s; t; t = (t - 1) & s)
			if(t >> x & 1)
				f[s] = (f[s] + 1ll * f[s ^ t] * cnt[t]) % mod;
	}
	init(U + 2);
	int ans = 0;
	rep(s, 0, U) ans = (ans + 1ll * phi[s + 1] * f[s] % mod) % mod;
	int ct = 0; rep(i, 1, n) ct += a[i] == 0;
	ans = ans * qp(2, ct) % mod; printf("%d\n", ans); return 0;
}
