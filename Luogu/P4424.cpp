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

const int N = 5010;
const int mod = 1e9 + 7;

int n, m, q, pw[N], val[N];
string t;
pair < string, int > s[N];

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in, m = in, q = in; rep(i, 1, m) s[i].se = i;
	rep(i, 1, n) {
		cin >> t;
		rep(j, 1, m) s[j].fi = t[j - 1] + s[j].fi;
	}
	sort(s + 1, s + m + 1);
	pw[0] = 1; rep(i, 1, n) pw[i] = pw[i - 1] * 2ll % mod;
	rep(i, 1, m) for(auto v : s[i].fi) val[i] = val[i] * 2ll % mod, val[i] += v - '0', val[i] %= mod;
	val[m + 1] = pw[n];
	rep(i, 1, q) {
		cin >> t;
		int l = 0, r = m + 1;
		per(i, m, 1) if(t[s[i].se - 1] != '1') { l = i; break; }
		rep(i, 1, m) if(t[s[i].se - 1] != '0') { r = i; break; }
		int ans = l <= r ? (val[r] - val[l] + mod) % mod : 0; printf("%d\n", ans);
	}
	return 0;
}
