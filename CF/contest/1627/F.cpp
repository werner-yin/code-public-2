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
const int T = 501;
const int INF = 1e9;

int n, K;
int lup[T][T], lus[T][T], ldp[T][T], lds[T][T], tot[T];
int f[T][T];
int a[N], b[N], c[N], d[N];

int tsolve() {
	map < pii, bool > hav[T][T];
	rep(i, 1, n) 
		hav[a[i]][b[i]][{ c[i], d[i] }] = true;
	rep(i, 0, K) rep(j, 0, K + 1) lup[i][j] = lus[i][j] = ldp[i][j] = lds[i][j] = 0;
	rep(i, 0, K) tot[i] = 0;
	rep(i, 1, n) if(a[i] == c[i]) tot[a[i]]++;
	rep(i, 1, K) rep(j, 1, K) {
		lup[i][j] = lup[i][j - 1] + hav[i][j][{ i - 1, j }];
	}
	rep(i, 1, K) per(j, K, 1) {
		lus[i][j] = lus[i][j + 1] + hav[i][j][{ i - 1, j }];
	}
	per(i, K, 1) rep(j, 1, K) {
		ldp[i][j] = ldp[i][j - 1] + hav[i][j][{ i + 1, j }];
	}
	per(i, K, 1) per(j, K, 1) {
		lds[i][j] = lds[i][j + 1] + hav[i][j][{ i + 1, j }];
	}
	rep(i, 0, K) rep(j, 0, K) f[i][j] = -INF;
	f[0][0] = 0; int res = 0;
	rep(i, 1, K / 2) {
		rep(k, 1, K) {
			int rv = tot[i] - hav[i][k][{ i, k + 1 }] + tot[K - i + 1] - hav[K - i + 1][K - k + 1][{K - i + 1, K - k}];
			rep(j, 0, K) if(f[i - 1][j] >= 0) {
				chkmax(f[i][k],
					   f[i - 1][j] + rv + lup[i][min(k, j)] + lus[i][max(k, j) + 1]
					   + ldp[K - i + 1][min(K - k + 1, K - j + 1)] + lds[K - i + 1][max(K - k + 1, K - j + 1) + 1]
					   );
			}
		}
	}
	rep(i, 1, K) chkmax(res, f[K / 2][i] + ldp[K / 2][i] + lds[K / 2][i + 1]);
	return res;
}

void solve() {
	n = in, K = in;
	rep(i, 1, n) {
		a[i] = in, b[i] = in, c[i] = in, d[i] = in;
	}
	int ans = tsolve();
	rep(i, 1, n) swap(a[i], b[i]), swap(c[i], d[i]);
	chkmax(ans, tsolve()); printf("%d\n", ans);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	for(int T = in; T; T--) solve();
	return 0;
}
