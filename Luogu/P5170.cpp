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
const int mod = 998244353;
const int inv2 = (mod + 1) >> 1;
const int inv3 = (mod + 1) / 3;

struct node {
	int f, g, h;
	node(int _f = 0, int _g = 0, int _h = 0) : f(_f), g(_g), h(_h) { }
	void output() { printf("%d %d %d\n", f, g, h); }
};

ll sq(int x) { return 1ll * x * x % mod; }
ll s0(int x) { return (x + 1) % mod; }
ll s1(int x) { return 1ll * x * (x + 1) / 2 % mod; }
ll s2(int x) { return 1ll * x * (x + 1) % mod * (2 * x + 1) % mod * inv2 % mod * inv3 % mod; }

node solve(int a, int b, int c, int n) {
	if(a == 0) return node(s0(n) * (b / c) % mod, s0(n) * sq(b / c) % mod, 1ll * s1(n) * (b / c) % mod);
	else if(a >= c || b >= c) {
		node t = solve(a % c, b % c, c, n), cur;
		cur.f = (t.f + (a / c) * s1(n) % mod + (b / c) * s0(n) % mod) % mod;
		cur.g = (sq(a / c) * s2(n) % mod + sq(b / c) * s0(n) % mod
				 + 2ll * (a / c) % mod * (b / c) % mod * s1(n) % mod
				 + 2ll * (a / c) % mod * t.h % mod
				 + 2ll * (b / c) % mod * t.f % mod
				 + t.g) % mod;
		cur.h = ((a / c) * s2(n) % mod + (b / c) * s1(n) % mod + t.h) % mod;
		return cur;
	} else {
		int M = (1ll * a * n + b) / c;
		node t = solve(c, c - b - 1, a, M - 1), cur;
		cur.f = (mod + 1ll * n * M % mod - t.f) % mod;
		cur.g = (mod + 2 * s1(M) * n % mod - 2ll * t.h % mod + mod - 2ll * t.f % mod + mod - cur.f) % mod;
		cur.h = (M * s1(n) % mod + mod - 1ll * inv2 * t.g % mod + mod - 1ll * inv2 * t.f % mod) % mod;
		return cur;
	}
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	for(int T = in, n, a, b, c; T; T--) n = in, a = in, b = in, c = in, solve(a, b, c, n).output();
	return 0;
}
