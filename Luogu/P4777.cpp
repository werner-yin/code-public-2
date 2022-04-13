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

ll x, M, n, a[N], b[N], X, Y, G;
ll mul(ll x, ll y, ll mod) { return __int128(x) * y % mod; }

void exgcd(ll a, ll b) {
	if(b == 0) return X = 1, Y = 0, G = a, void();
	exgcd(b, a % b); ll tx = X; X = Y, Y = tx - a / b * Y;
}

pair < ll, ll > merge(ll x1, ll m1, ll x2, ll m2) {
	ll m3 = m1 / __gcd(m1, m2) * m2; x2 = ((x2 - x1) % m2 + m2) % m2;
	exgcd(m1, m2); if(x2 % G) return { -1, m3 };
	X = (X % m2 + m2) % m2; X = mul(X, x2 / G, m2); X = (x1 + mul(X, m1, m3)) % m3;
	return { X, m3 };
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in; rep(i, 1, n) a[i] = lin, b[i] = lin;
	x = 0, M = 1; rep(i, 1, n) tie(x, M) = merge(x, M, b[i], a[i]);
	printf("%lld\n", x);
	return 0;
}
