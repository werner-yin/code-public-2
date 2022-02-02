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

const int N = 1e5 + 10;

int n;
char s[N];
int cnt[N], rk[N], ork[N << 1], sa[N], px[N], id[N], ht[N];
int mn[21][N], lg[N], pw[30];
int t[N];

int lcp(int x, int y) {
	x = rk[x], y = rk[y]; if(x > y) swap(x, y);
	x++; int k = lg[y - x + 1];
	return min(mn[k][x], mn[k][y - pw[k] + 1]);
}

void getSA(int *s) {
	int m = n + 1;
	rep(i, 1, n) s[i]++, ++cnt[rk[i] = s[i]];
	rep(i, 1, m) cnt[i] += cnt[i - 1];
	per(i, n, 1) sa[cnt[rk[i]]--] = i;
	for(int h = 1, p; h <= n; h <<= 1, m = p) {
		p = 0; per(i, n, n - h + 1) id[++p] = i;
		rep(i, 1, n) if(sa[i] > h) id[++p] = sa[i] - h;
		rep(i, 0, m) cnt[i] = 0;
		rep(i, 1, n) ++cnt[px[i] = rk[id[i]]];
		rep(i, 1, m) cnt[i] += cnt[i - 1];
		per(i, n, 1) sa[cnt[px[i]]--] = id[i];
		rep(i, 1, n) ork[i] = rk[i];
		auto cmp = [&](auto a, auto b) { return ork[a] == ork[b] && ork[a + h] == ork[b + h]; };
		p = 0; rep(i, 1, n) rk[sa[i]] = cmp(sa[i], sa[i - 1]) ? p : ++p;
	}
	int p = 0;
	rep(i, 1, n) {
		if(p) p--;
		while(s[i + p] == s[sa[rk[i] - 1] + p]) p++;
		ht[rk[i]] = p;
	}
	rep(i, 2, n) lg[i] = lg[i >> 1] + 1;
	pw[0] = 1; rep(i, 1, lg[n]) pw[i] = pw[i - 1] << 1;
	rep(i, 1, n) mn[0][i] = ht[i];
	rep(k, 1, lg[n])
		rep(i, 1, n - pw[k] + 1) mn[k][i] = min(mn[k - 1][i], mn[k - 1][i + pw[k - 1]]);
}

int pos[30], p[N][30];

int exlcp(int x, int y) {
	int u[30] = { 0 }, v[30] = { 0 }, c1 = 0, c2 = 0;
	rep(i, 0, 25) if(p[x][i]) u[++c1] = p[x][i];
	rep(i, 0, 25) if(p[y][i]) v[++c2] = p[y][i];
	sort(u + 1, u + c1 + 1); sort(v + 1, v + c2 + 1);
	int len = 0;
	rep(i, 1, min(c1, c2)) {
		len++; int tlen = lcp(u[i] + 1, v[i] + 1);
		if(u[i + 1] - u[i] == v[i + 1] - v[i] && tlen + u[i] >= u[i + 1] - 1) len += u[i + 1] - u[i] - 1;
		else { len += tlen; break; }
	} return len;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in; scanf("%s", s + 1);
	rep(i, 1, n) {
		if(pos[s[i] - 'a']) t[i] = i - pos[s[i] - 'a'];
		pos[s[i] - 'a'] = i;
	} getSA(t);
	rep(i, 0, 25) pos[i] = 0;
	per(i, n, 1) {
		pos[s[i] - 'a'] = i;
		rep(j, 0, 25) p[i][j] = pos[j];
	} iota(id + 1, id + n + 1, 1);
	sort(id + 1, id + n + 1, [](auto a, auto b) {
		int l = exlcp(a, b);
		if(a + l > n || b + l > n) return a > b;
		int u = p[a][s[a + l] - 'a'] == a + l ? 0 : t[a + l];
		int v = p[b][s[b + l] - 'a'] == b + l ? 0 : t[b + l];
		return u < v;
	});
	ll ans = 1ll * n * (n + 1) / 2;
	rep(i, 2, n) ans -= exlcp(id[i - 1], id[i]);
	printf("%lld\n", ans);
	return 0;
}
