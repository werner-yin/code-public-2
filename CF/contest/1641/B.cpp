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

const int N = 510 + 10;

vec arr, len;
veg ans;
int n, pt;

void solve() {
	n = in; arr.clear(); len.clear(); ans.clear(); pt = 0;
	rep(i, 1, n) arr.eb(in); map < int, int > cnt; for(auto v : arr) cnt[v]++;
	for(auto v : cnt) if(v.se & 1) return puts("-1"), void();
	while(arr.size()) {
		int p = -1;	rep(i, 1, arr.size() - 1) if(arr[i] == arr[0]) { p = i; break; }
		len.eb(p * 2); rep(i, 1, p - 1) ans.eb(p + i + pt - 1, arr[i]);
		pt += p * 2; arr.erase(arr.begin() + p); arr.erase(arr.begin());
		if(p > 2) reverse(arr.begin(), arr.begin() + p - 1);
	} printf("%ld\n", ans.size());
	for(auto v : ans) printf("%d %d\n", v.fi + 1, v.se);
	printf("%d\n", len.size());
	for(auto v : len) printf("%d ", v); puts("");
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	for(int T = in; T; T--) solve();
	return 0;
}
