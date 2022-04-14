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

ll n;

ll mul(ll x, ll y, ll mod) { return (__int128) x * y % mod; }
ll qp(ll x, ll t, ll mod) { ll res = 1; for(; t; t >>= 1, x = mul(x, x, mod)) if(t & 1) res = mul(res, x, mod); return res; }

bool miller_rabbin(ll a, ll n) {
	ll d = n - 1, t = 0; while(~d & 1ll) d >>= 1, t++;
    ll x = qp(a, d, n); if(x == 1 || x == n - 1) return true;
	rep(i, 1, t) {
		if(x == 1 || x == n - 1) return true;
		x = mul(x, x, n);
	} return false;
}

const int tp[] = { 2, 3, 5, 7, 11, 13, 31 };

bool isprime(ll x) {
	if(x <= 1) return false;
	for(auto v : tp) {
		if(x == v) return true;
		if(!miller_rabbin(v, x)) return false;
	} return true;
}

random_device tnd;
mt19937_64 rnd(tnd());

ll mxfac = 0;

ll f(ll x, ll c, ll n) { return (mul(x, x, n) + c) % n; }

ll pollard_rho(ll n) {
	ll c = rnd() % (n - 1) + 1, cur1 = 0; 
	for(int st = 1, ed = 2; ; st <<= 1, ed <<= 1) {
		ll cur2 = cur1, prod = 1, ct = 0;
		rep(i, st, ed) {
			cur2 = f(cur2, c, n); prod = mul(prod, ((cur2 - cur1) + n) % n, n); ct++;
			if(ct == 127) {
				ct = 0; ll t = __gcd(n, prod); if(t != 1) return t;
			}
		} ll t = __gcd(n, prod); if(t != 1) return t; cur1 = cur2; 
	}
}

void factorize(ll n) {
	if(isprime(n)) return chkmax(mxfac, n);
	if(n <= 1) return;
	ll t; while((t = pollard_rho(n)) == n);
	factorize(t), factorize(n / t);
}

void solve() { n = lin; mxfac = 0; if(isprime(n)) return puts("Prime"), void(); factorize(n); printf("%lld\n", mxfac); }

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	int T = in; while(T--) solve(); return 0;
}
