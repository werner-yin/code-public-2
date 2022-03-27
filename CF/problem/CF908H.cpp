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

const int N = 50;

int n, fa[N], id[N], tot, siz[N], U;
ll f[1 << 23], g[1 << 23], w[1 << 23];
bool ban[N][N];
char s[N][N];

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in; rep(i, 1, n) scanf("%s", s[i] + 1);
	function < int(int) > gf = [&](auto x) { return fa[x] == x ? x : fa[x] = gf(fa[x]); };
	rep(i, 1, n) fa[i] = i; 
	rep(i, 1, n) rep(j, 1, n) if(s[i][j] == 'A') fa[gf(i)] = gf(j);
	rep(i, 1, n) rep(j, 1, n) if(s[i][j] == 'X' && gf(i) == gf(j)) return puts("-1"), 0;
	rep(i, 1, n) siz[gf(i)]++; rep(i, 1, n) if(gf(i) == i && siz[gf(i)] > 1) id[i] = tot++;
	bool fl = 1; rep(i, 1, n) fl &= siz[gf(i)] == 1; if(fl) return printf("%d\n", n - 1), 0;
	rep(i, 1, n) rep(j, 1, n) if(s[i][j] == 'X' && siz[gf(i)] > 1 && siz[gf(j)] > 1) ban[id[gf(i)]][id[gf(j)]] = true;
	rep(i, 0, tot - 1) g[1 << i] = 1; U = 1 << tot; U--;
	//rep(i, 0, tot - 1) { rep(j, 0, tot - 1) cerr << ban[i][j] << " "; cerr << endl; }
	rep(s, 0, U) if(g[s]) {
		rep(i, 0, tot - 1) if(~s >> i & 1) {
			bool fl = false; rep(j, 0, tot - 1) fl |= (s >> j & 1 && ban[i][j]);
			if(fl) continue; g[s | 1 << i] = 1;
		}
	} //rep(s, 0, U) cerr << g[s] << " "; cerr << endl;
	rep(s, 0, U) w[s] = (tot - __builtin_parity(s)) & 1 ? -1 : 1;
	auto FMT = [&](auto f) { // OR convolution
		rep(i, 0, tot - 1)
			rep(s, 0, U) if(s >> i & 1)
			f[s] += f[s ^ 1 << i];
	};
	FMT(g); f[0] = 1; FMT(f); //rep(i, 0, U) cerr << f[i] << " "; cerr << endl;
	rep(i, 0, n) {
		ll res = 0;
		rep(s, 0, U) f[s] = f[s] * g[s], res += f[s] * w[s];
		if(res) return printf("%d\n", n + i), 0;
	}
	return 0;
}
