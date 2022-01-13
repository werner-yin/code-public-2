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

const int N = 2e6 + 10;

ll g[N][15], lim, w[N], s[N][15], n;
int m, p[N], tot, pri[N], ind1[N], ind2[N], pnum;
bool v[N];

void shai(int l) {
	rep(i, 2, l) {
		if(!v[i]) {
			pri[++pnum] = i;
			rep(j, 0, m - 1) s[pnum][j] = s[pnum - 1][j];
			s[pnum][i % m]++;
		}
		rep(j, 1, pnum) {
			if(pri[j] * i > l) break;
			v[pri[j] * i] = true; if(i % pri[j] == 0) break;
		}
	}
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = lin, m = in; lim = sqrtl(n);
	shai(lim);
	for(ll i = 1; i <= n; i++) {
		++tot; w[tot] = n / i;
		if(w[tot] <= lim) ind1[w[tot]] = tot; else ind2[n / w[tot]] = tot;
		rep(j, 0, m - 1)
			g[tot][j] = (w[tot]) / m + (w[tot] % m >= j) - (j <= 1);
		i = n / (n / i);
	} 
	rep(i, 1, pnum) {
		int p = pri[i]; 
		rep(j, 1, tot) {
			if(1ll * p * p > w[j]) break;
			int t = w[j] / p <= lim ? ind1[w[j] / p] : ind2[n / (w[j] / p)];
			rep(k, 0, m - 1)
				g[j][k * p % m] -= g[t][k] - s[i - 1][k];
		}
	} rep(i, 0, m - 1) printf("%lld\n", g[1][i]);
	return 0;
}
