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

const int N = 1 << 17;

int b[20], c[N], id[N], n, m;

bool ins(int x) {
	per(i, n - 1, 0)
		if(x >> i & 1) {
			if(!b[i]) return b[i] = x, true;
			else x ^= b[i];
		} return false;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in, m = 1 << n;
	rep(i, 1, m - 1) c[i] = in, id[i] = i;
	sort(id, id + m, [](auto a, auto b) { return c[a] < c[b]; });
	ll ans = 0;
	rep(i, 0, m - 1) {
		if(ins(id[i])) ans += c[id[i]];
	} cout << ans << endl;
	return 0;
}
