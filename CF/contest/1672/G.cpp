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

const int N = 2010;
const int mod = 998244353;

int n, m,  val[N << 1], tot, ret, siz;
char s[N][N];
ll ans = 1;
vec G[N << 1];
bool vis[N << 1];

ll qp(ll x, int t = mod - 2) { ll res = 1; for(; t; t >>= 1, x = x * x % mod) if(t & 1) res = res * x % mod; return res; }

void dfs(int x) {
	ret ^= val[x]; tot += G[x].size(); siz++; vis[x] = true;
	for(auto y : G[x]) if(!vis[y]) dfs(y);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in, m = in; rep(i, 1, n) scanf("%s", s[i] + 1);
	if(n % 2 == 0 && m % 2 == 0) {
		rep(i, 1, n) rep(j, 1, m) if(s[i][j] == '?') ans = ans * 2ll % mod;
		cout << ans << endl; return 0;
	}
	if(m % 2 == 0) {
		rep(i, 1, n) rep(j, i + 1, m) swap(s[i][j], s[j][i]);
		swap(n, m);
	}
	if(n % 2 == 0) {
		ll ans1 = 1, ans2 = 1;
		rep(i, 1, n) {
			int cnt = 0, ret = 0;
			rep(j, 1, m) cnt += s[i][j] == '?', ret ^= s[i][j] == '1';
			if(cnt == 0) (ret ? ans1 : ans2) = 0;
			else ans1 = ans1 * qp(2, cnt - 1) % mod, ans2 = ans2 * qp(2, cnt - 1) % mod;
		} ans = (ans1 + ans2) % mod; cout << ans << endl; return 0;
	}
	ll ans1 = 1, ans2 = 1;
	rep(i, 1, n) 
		rep(j, 1, m)
		if(s[i][j] == '?') G[i].eb(j + n), G[j + n].eb(i);
		else val[i] ^= s[i][j] - '0', val[j + n] ^= s[i][j] - '0';
	rep(i, 1, n + m) if(!vis[i]) {
		tot = 0, siz = 0, ret = 0; dfs(i); tot /= 2; tot -= siz - 1; tot = qp(2, tot);
		//cerr << tot << " " << siz << " " << ret << endl; 
		if(siz & 1) {
			if(ret == 0) ans1 = ans1 * tot % mod, ans2 = 0;
			else ans1 = 0, ans2 = ans2 * tot % mod;
		} else {
			if(ret == 1) tot = 0;
			ans1 = ans1 * tot % mod, ans2 = ans2 * tot % mod;
		}
		//cerr << ans1 << " " << ans2 << endl;
	} cout << (ans1 + ans2) % mod << endl;
	return 0;
}
