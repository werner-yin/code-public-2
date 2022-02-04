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

const int N = 2e5 + 10;
const int mod = 998244353;
const int inv2 = (mod + 1) >> 1;

int n, K, iv, ans;

ll qp(ll x, int t) { ll res = 1; for(; t; t >>= 1, x = x * x % mod) if(t & 1) res = res * x % mod; return res; }

struct node {
	int a, b, c; // a : 不交, b : 被包含, c : 不被包含但是有交
	node(int l, int r) {
		a = (1ll * l * (l - 1) / 2 % mod * iv % mod + 1ll * (n - r + 1) * (n - r) / 2 % mod * iv % mod) % mod;
		b = 1ll * l * (n - r + 1) % mod * iv % mod;
		c = (mod * 2 - a - b + 1) % mod;
	} node(int _a, int _b, int _c) : a(_a), b(_b), c(_c) { }
	node() { a = b = c = 0; }
};

struct mat {
	int a[4][4];
	mat() { memset(a, 0, sizeof a); }
	int* operator [](int x) { return a[x]; }
	friend mat operator * (mat a, mat b) {
		mat c;
		rep(i, 0, 3) rep(j, 0, 3) if(a[i][j])
			rep(k, 0, 3) c[i][k] = (c[i][k] + 1ll * a[i][j] * b[j][k] % mod) % mod;
		return c;
	}
} t;
	
void solve(int l, int r, const node &lst) {
	t = mat(); node c(l, r);
	ll A = lst.a, B = lst.b, C = (c.a - lst.a + mod) % mod, D = (c.b - lst.b + mod) % mod, E = (1ll - A - B - C - D + mod * 4ll) % mod;
	
	//A = A * qp(iv, mod - 2) % mod; B = B * qp(iv, mod - 2) % mod; C = C * qp(iv, mod - 2) % mod;
	//D = D * qp(iv, mod - 2) % mod; E = E * qp(iv, mod -2) % mod;
	//cerr << A << " " << B << " " << C << " " << D << " " << E << " | " << l << " " << r << endl;
	
	t[0][0] = (A + C + E) % mod; t[0][1] = D;                 t[0][2] = B;
	t[1][0] = E;                 t[1][1] = (A + C + D) % mod;                              t[1][3] = B;
	t[2][0] = E;                 t[2][1] = (C + D) % mod;     t[2][2] = (A + B) % mod; 
	t[3][0] = E;                 t[3][1] = (C + D) % mod;     t[3][2] = 0;                 t[3][3] = (A + B) % mod;
	
	//t[0][0] = (A + C) % mod; t[2][0] = E;
	//t[1][1] = (A + C) % mod; t[2][1] = D; t[2][2] = 1;
	mat res = t; for(int v = K - 1; v; v >>= 1, t = t * t) if(v & 1) res = res * t;
	//assert(((ll)res[0][0] + res[0][1] + res[0][2] + res[0][3]) % mod == 1);
	ans = (ans + res[0][1]) % mod; ans = (ans + res[0][3]) % mod;
	//cerr << (res[0][1] + res[0][3]) % mod << endl;
	if(l == r) return; int mid = in; solve(l, mid, c); solve(mid + 1, r, c);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in, K = in; iv = qp(1ll * n * (n + 1) / 2 % mod, mod - 2);
	solve(1, n, node(0, 0, 1)); printf("%d\n", ans); return 0;
}
