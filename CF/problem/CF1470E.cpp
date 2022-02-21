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

const int N = 5e5 + 10;

__int128 f[N][5];
int n, K, q, p[N];
veg g[N][5];
//pii vvv[N][5][5];

namespace sub1 {
	int a[N];
	int get(ll x, int y, pii cur = { 1, K }) {
		pii lst = { 0, 0 };
		while(cur.fi <= y) {
			lst = cur;
			for(const auto &v : g[cur.fi][cur.se]){
				ll t = f[v.fi][v.se];
				if(x > t) x -= t;
				else { cur = v; break; }
			}
		} rep(i, lst.fi, cur.fi) a[i] = p[i];
		reverse(a + lst.fi, a + cur.fi);
		return a[y];
	}
	void solve() {
		while(q--) {
			ll x = lin; int y = in;
			if(x > f[1][K]) puts("Wormhole station overwhelmed");
			else printf("%d\n", get(x, y));
		}
	}
}

int B;

namespace sub2 {
	__int128 c0[N][5];
	int get(ll x, int y) {
		pii cur = { 1, K };
		while(cur.fi <= y) {
			if(y - cur.fi <= 10) return sub1 :: get(x, y, cur);
			int l = 0, r = y - cur.fi - 10;
			while(l <= r) {
				int mid = l + r >> 1;
				if(c0[cur.fi + mid - 1][cur.se] - c0[cur.fi - 1][cur.se] < x
				   && c0[cur.fi + mid - 1][cur.se] - c0[cur.fi - 1][cur.se] + f[cur.fi + mid][cur.se] >= x)
					l = mid + 1;
				else r = mid - 1;
			}
			x -= c0[cur.fi + r - 1][cur.se] - c0[cur.fi - 1][cur.se], cur.fi = cur.fi + r;
			for(const auto &v : g[cur.fi][cur.se]) {
				ll t = f[v.fi][v.se];
				if(x > t) x -= t;
				else { cur = v; break; }
			}
		} assert(0);
	}
	void solve() {
		rep(i, 1, n)
			rep(j, 0, K) {
			for(auto v : g[i][j])
				if(v.fi - i != 1) c0[i][j] += f[v.fi][v.se];
				else break;
		}
		rep(i, 1, n) rep(j, 0, K) c0[i][j] += c0[i - 1][j];
		while(q--) {
			int y = in; ll x = lin;
			if(x > f[1][K]) puts("-1");
			else printf("%d\n", get(x, y));
		}
		rep(i, 0, n + 2) rep(j, 0, K) c0[i][j] = 0;
	}
}

template < typename T > void ewrite(T x) {
	vec pot; while(x > 0) pot.eb(x % 10), x /= 10;
	reverse(pot.begin(), pot.end());
	for(auto v : pot) cerr << v ; cerr << endl;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	for(int T = in; T; T--) {
		n = in; K = in, q = in; rep(i, 1, n) p[i] = in;
		rep(i, 0, K) f[n + 1][i] = 1;
		per(i, n, 1)
			rep(j, 0, K) {
			vec cur; rep(t, i, i + j) cur.eb(p[t]);
			vector < pair < vec, int > > al;
			rep(t, 0, j) {
				f[i][j] += f[i + t + 1][j - t];
				vec tcur = cur; reverse(tcur.begin(), tcur.begin() + t + 1);
				al.eb(tcur, t);
			} sort(al.begin(), al.end());
			rep(t, 0, j) g[i][j].eb(i + al[t].se + 1, j - al[t].se);
		} 
		sub2 :: solve();
		rep(i, 0, n + 1) rep(j, 0, K) f[i][j] = 0, g[i][j].clear();
	}
	return 0;
}
