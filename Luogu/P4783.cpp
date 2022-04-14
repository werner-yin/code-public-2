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

const int N = 810;
const int mod = 1e9 + 7;

int n, a[N][N];

ll qp(ll x, int t = mod - 2) { ll res = 1; for(; t; t >>= 1, x = x * x % mod) if(t & 1) res = res * x % mod; return res; }

void guass(int mat[N][N]) {
	rep(i, 1, n) {
		int p = -1; rep(j, i, n) if(mat[j][i]) { p = j; break; }
		if(p == -1) return puts("No Solution"), exit(0), void(); if(p ^ i) swap(mat[p], mat[i]); ll vt = qp(mat[i][i]);
		rep(j, 1, n) if(j ^ i) {
			ll t = 1ll * mat[j][i] * vt % mod;
			rep(k, i, n << 1) mat[j][k] = (mat[j][k] - 1ll * t * mat[i][k] % mod + mod) % mod;
		}
		rep(j, i, n << 1) mat[i][j] = 1ll * mat[i][j] * vt % mod;
	}
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in; rep(i, 1, n) rep(j, 1, n) a[i][j] = in;
	rep(i, 1, n) a[i][i + n] = 1;
	guass(a); rep(i, 1, n) { rep(j, n + 1, n + n) printf("%d ", a[i][j]); puts(""); }
	return 0;
}
