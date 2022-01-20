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
const int mod = 1e9 + 7;
const int inv100 = 570000004;

int a[N], b[N], n;

ll qp(ll x, int t = mod - 2) { ll res = 1; for(; t; t >>= 1, x = x * x % mod) if(t & 1) res = res * x % mod; return res; }
int calc(int v) { // 1 + v + v ^ 2 + v ^ 3 + ...
	if(v == 0) return 1;
	return qp((1 + mod - v) % mod);
}
void out(int x, int y) { cerr << 1ll * x * qp(y) % mod << endl; }

struct node {
	int a1, a2, a3, a4;
	void set(int x, int y) {
		int ta1, ta2, ta3, ta4;
		ll v = calc(1ll * a3 * y % mod);
		ta1 = 1ll * a1 * x % mod * v % mod;
		// cerr << "!" << 1ll * a1 * x % mod << " " ; out(2, 5); out(1, 100);
		// cerr << "|" << 1ll * a3 * y % mod << " " << calc(1ll * a3 * y % mod) << endl;
		ta2 = (a2 + 1ll * a1 * a4 % mod * y % mod * v % mod) % mod;
		ta3 = (y + 1ll * x * a3 % mod * x % mod * v % mod) % mod;
		ta4 = 1ll * x * a4 % mod * v % mod;
		a1 = ta1; a2 = ta2; a3 = ta3; a4 = ta4;
	}
};
	
int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in; rep(i, 1, n) a[i] = 1ll * in * inv100 % mod, b[i] = 1ll * in * inv100 % mod;
	node cur; cur.a1 = cur.a4 = a[1]; cur.a2 = cur.a3 = b[1];
	rep(i, 2, n) cur.set(a[i], b[i]);
	printf("%d\n", cur.a1);
	return 0;
}
