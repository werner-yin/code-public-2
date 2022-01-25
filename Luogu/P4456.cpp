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
const int M = 190;

int n, mod, a, b, siz;

struct mat { // 0 ~ a + b, a + b + 1 ~ (a + b + 1) + (a + b)
	int arr[M][M];
	mat() { memset(arr, 0, sizeof arr); }
	int* operator [](int x) { return arr[x]; }
	friend mat operator * (mat a, mat b) {
		mat c;
		rep(i, 0, siz)
			rep(j, 0, siz) if(a[i][j])
				rep(k, 0, siz) 
					c[i][k] = (c[i][k] + 1ll * a[i][j] * b[j][k] % mod) % mod;
		return c;
	}
} per, cur;

int fac[510], ifac[510];

ll qp(ll x, int t) { ll res = 1; for(; t; t >>= 1, x = x * x % mod) if(t & 1) res = 1ll * res * x % mod; return res; }

void init(int l) {
	fac[0] = 1; rep(i, 1, l) fac[i] = 1ll * fac[i - 1] * i % mod;
	ifac[l] = qp(fac[l], mod - 2); per(i, l - 1, 0) ifac[i] = 1ll * ifac[i + 1] * (i + 1) % mod;	
}

ll C(int x, int y) { return x < 0 || y < 0 || x < y ? 0 : 1ll * fac[x] * ifac[y] % mod * ifac[x - y] % mod; }

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in, a = in, b = in, mod = in;
	init(a + b + 10);
	siz = (a + b) * 2 + 1;
	rep(i, 0, 1)
		rep(j, 0, 1)
			if(!i || !j) {
				rep(t, 0, a + b)
					rep(k, 0, t) {
						int id1 = i * (a + b + 1) + k, id2 = j * (a + b + 1) + t;
						if(j == 1) per[id1][id2] = C(t, k);
						else per[id1][id2] = k == t;
					}
			}
	cur[0][0] = 1;
	for(int t = n; t; t >>= 1, per = per * per) if(t & 1) cur = cur * per;
	int ans = 0;
	rep(_, 0, 1)
		rep(i, 0, a) {
			int res = qp(n, i) * C(a, i) % mod * cur[0][(a + b + 1) * _ + a + b - i] % mod;
			if((a - i) & 1) ans = (ans + mod - res) % mod;
			else ans = (ans + res) % mod;
		}
	printf("%d\n", ans);
	return 0;
}