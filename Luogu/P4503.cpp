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
using ull = unsigned long long;
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

const int N = 3e4 + 10;
const ull base = 13331;

int n, L, S;
char s[210];
ull pre[N][210], suf[N][210], pw[210];
ll ans;

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in, L = in, S = in;
	pw[0] = 1; rep(i, 1, L) pw[i] = pw[i - 1] * base;
	rep(i, 1, n) {
		scanf("%s", s + 1);
		rep(j, 1, L) pre[i][j] = pre[i][j - 1] * base + s[j];
		per(j, L, 1) suf[i][j] = s[j] * pw[L - j] + suf[i][j + 1];
	}
	rep(i, 1, L) {
		unordered_map < ull, int > t;
		rep(j, 1, n) {
			ull res = pre[j][i - 1] * pw[L - i + 1] + suf[j][i + 1];
			t[res] += 1;
		}
		for(auto v : t) ans += 1ll * v.se * (v.se - 1) / 2;
	} printf("%lld\n", ans);
	return 0;
}
