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

char s[N];
int cnt[N], m, n, id[N], rk[N], sa[N], px[N], ork[N << 1];

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	scanf("%s", s + 1); n = strlen(s + 1); m = 300;
	rep(i, 1, n) ++cnt[rk[i] = s[i]];
	rep(i, 1, m) cnt[i] += cnt[i - 1];
	per(i, n, 1) sa[cnt[rk[i]]--] = i;
	for(int h = 1, p; h <= n; h <<= 1, m = p) {
		p = 0; per(i, n, n - h + 1) id[++p] = i;
		rep(i, 1, n) if(sa[i] > h) id[++p] = sa[i] - h;
		rep(i, 1, m) cnt[i] = 0;
		rep(i, 1, n) ++cnt[px[i] = rk[id[i]]];
		rep(i, 1, m) cnt[i] += cnt[i - 1];
		per(i, n, 1) sa[cnt[px[i]]--] = id[i];
		rep(i, 1, n) ork[i] = rk[i];
		auto cmp = [&](int x, int y) { return ork[x] == ork[y] && ork[x + h] == ork[y + h]; };
		p = 0; rep(i, 1, n) rk[sa[i]] = cmp(sa[i], sa[i - 1]) ? p : ++p;
	} rep(i, 1, n) printf("%d ", sa[i]); puts("");
	return 0;
}
