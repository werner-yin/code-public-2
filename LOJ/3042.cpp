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

const int M = 2100;
const int N = 410;
const int inf = 0x3f3f3f3f;
const int mod = 998244353;

struct mat {
	int a[3][3];
	mat() { memset(a, -1, sizeof a); }
	int *operator [](int x) { return a[x]; }
	const int *operator [](int x) const { return a[x]; }
	void upd(const mat &x) { rep(i, 0, 2) rep(j, 0, 2) chkmax(a[i][j], x[i][j]); }
	mat append(int x) {
		mat res;
		rep(i, 0, 2) rep(j, 0, 2) if(a[i][j] != -1) rep(k, 0, 2) if(x >= i + j + k)
			chkmax(res[j][k], min(a[i][j] + i + (x - i - j - k) / 3, 4));
		return res;
	}
};

struct stnode {
	mat dp[2]; int pacnt;
	stnode() { dp[0] = dp[1] = mat(); pacnt = 0; }
	friend bool operator < (stnode x, stnode y) {
		rep(p, 0, 1) rep(i, 0, 2) rep(j, 0, 2) if(x.dp[p][i][j] != y.dp[p][i][j]) return x.dp[p][i][j] < y.dp[p][i][j];
		return x.pacnt < y.pacnt;
	}
	stnode append(int x) {
		stnode tres; tres.dp[0].upd(dp[0].append(x)); tres.dp[1].upd(dp[1].append(x));
		tres.pacnt = pacnt + (x >= 2); if(x >= 2) tres.dp[1].upd(dp[0].append(x - 2)); return tres;
	}
};

bool check(const stnode &x) {
	if(x.pacnt >= 7) return true;
	rep(j, 0, 2) rep(k, 0, 2) if(x.dp[1][j][k] >= 4) return true;
	return false;
}
stnode winstu() { stnode res; res.pacnt = inf; return res; }

vec G[M];
map < stnode, int > ind;
int tot, n, winid, cnt[N], f[2][N][M], fac[N], ifac[N];
queue < stnode > q;

void build() {
	stnode st; st.dp[0][0][0] = 0; ind[st] = ++tot; q.ep(st);
	while(q.size()) {
		stnode x = q.front(); q.pop(); int id = ind[x];
		rep(i, 0, 4) {
			stnode y = x.append(i); if(check(y)) y = winstu();
			if(ind.count(y)) G[id].eb(ind[y]);
			else G[id].eb(++tot), ind[y] = tot, q.ep(y);
		}
	}
}

ll qp(ll x, int t = mod - 2) { ll res = 1; for(; t; t >>= 1, x = x * x % mod) if(t & 1) res = res * x % mod; return res; }

ll C(int x, int y) { return x < 0 || y < 0 || x < y ? 0 : 1ll * fac[x] * ifac[y] % mod * ifac[x - y] % mod; }

void init(int l) {
	fac[0] = 1; rep(i, 1, l) fac[i] = 1ll * fac[i - 1] * i % mod; ifac[l] = qp(fac[l]);
	per(i, l - 1, 0) ifac[i] = 1ll * ifac[i + 1] * (i + 1) % mod; 
}

int ans;

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	build(); winid = ind[winstu()]; //cerr << "!" << winid << endl;
	n = in; rep(i, 1, 13) { cnt[in]++; in; }
	init(n * 4); int o = 0; f[o][0][1] = 1;
	rep(i, 1, n) {
		memset(f[o ^ 1], 0, sizeof f[o ^ 1]);
		rep(j, 0, 4 * (i - 1)) rep(k, 1, tot) if(f[o][j][k])
			rep(t, 0, 4 - cnt[i])
				if(G[k][t + cnt[i]] != winid)
					(f[o ^ 1][j + t][G[k][t + cnt[i]]] += f[o][j][k] * C(4 - cnt[i], t) % mod) %= mod;
		o ^= 1;
	} rep(j, 1, 4 * n - 13) rep(k, 1, tot) if(f[o][j][k]) (ans += qp(C(4 * n - 13, j)) * f[o][j][k] % mod) %= mod;
	printf("%d\n", ans + 1);
	return 0;
}
