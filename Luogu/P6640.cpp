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

char s[N], t[N], ts[N];
int n, m, pmn[N], smn[N], val[N];
int cnt[N], sa[N], rk[N], ork[N], px[N], id[N], ht[N];

int getSA(char *s, int len) {
	int n = len, m = 300;
	rep(i, 1, m) cnt[i] = 0;
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
	}
	for(int i = 1, p = 0; i <= n; i++) {
		if(p) p--;
		while(s[i + p] == s[sa[rk[i] - 1] + p]) p++;
		ht[rk[i]] = p;
	} //rep(i, 1, n) cerr << ht[i] << endl;
}

int lg[N], pw[30], mx[21][N];
void initST(int *val, int len) {
	rep(i, 2, len) lg[i] = lg[i >> 1] + 1;
	pw[0] = 1; rep(i, 1, lg[len]) pw[i] = pw[i - 1] << 1;
	rep(i, 1, len) mx[0][i] = val[i];
	rep(k, 1, lg[len]) rep(i, 1, len - pw[k] + 1) mx[k][i] = max(mx[k - 1][i], mx[k - 1][i + pw[k - 1]]); 
}
int query(int l, int r) { int k = lg[r - l + 1]; return max(mx[k][l], mx[k][r - pw[k] + 1]); }

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	scanf("%s", s + 1); n = strlen(s + 1); scanf("%s", t + 1); m = strlen(t + 1);
	rep(i, 1, n) ts[i] = s[i]; ts[n + 1] = '#'; 
	rep(i, 1, m) ts[n + 1 + i] = t[i]; getSA(ts, n + m + 1); 
	memset(pmn, 0x3f, sizeof pmn); memset(smn, 0x3f, sizeof smn);
	rep(i, 1, n + m + 1) {
		pmn[i] = pmn[i - 1];
		if(sa[i] > n + 1) pmn[i] = n + m + 1 - sa[i] + 1;
		else chkmin(pmn[i], ht[i]);
	}
	per(i, n + m + 1, 1) {
		smn[i] = smn[i + 1];
		if(sa[i] > n + 1) smn[i] = n + m + 1 - sa[i] + 1;
		else chkmin(smn[i], ht[i]);
	} rep(i, 1, n) val[i] = min(pmn[rk[i]], smn[rk[i]]);
	initST(val, n); int Q = in;
	while(Q--) {
		int l = in, r = in, L = 0, R = min(m, r - l + 1), ans = 0;
		while(L <= R) {
			int mid = L + R >> 1;
			if(query(l, r - mid + 1) >= mid) L = mid + 1, ans = mid;
			else R = mid - 1; 
		} printf("%d\n", ans);
	}
	return 0;
}
