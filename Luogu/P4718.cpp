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
const int pri[] = { 2, 3, 5, 7, 11, 13, 31 };

ll n, mxfac;
mt19937_64 rnd(time(NULL));

ll mul(ll a, ll b, ll mod) { return (__int128) a * b % mod; }

ll qp(ll x, ll t, ll mod) { ll res = 1; for(; t; t >>= 1, x = mul(x, x, mod)) if(t & 1) res = mul(res, x, mod); return res; }

bool miller_rabin(ll n, ll a) {
	ll d = n - 1, ct = 0; while(~d & 1ll) d >>= 1, ct++;
	ll x = qp(a, d, n); if(x == 1) return true;
	rep(i, 1, ct) {
		if(x == n - 1 || x == 1) return true;
		x = mul(x, x, n);
	} return false;
}

bool check_prime(ll n) {
	if(n < 2) return false;
	for(auto x : pri) {
		if(n == x) return true;
		if(!miller_rabin(n, x)) return false;
	} return true;
}

ll f(ll x, ll c, ll mod) { return (mul(x, x, mod) + c) % mod; }

ll pollard_rho(ll n) {
	ll c = rnd() % (n - 1) + 1; ll v1 = 0;
	for(int s = 1, t = 2; ; s <<= 1, t <<= 1) {
		ll pro = 1, v2 = v1, cnt = 0;
		rep(i, s + 1, t) {
			v2 = f(v2, c, n); pro = mul(pro, abs(v1 - v2), n); ++cnt;
			if(cnt % 127 == 0) {
				cnt = 0; ll d = __gcd(pro, n);
				if(d > 1) return d;
			} 
		} ll d = __gcd(pro, n); if(d > 1) return d; v1 = v2;
	}
}

void factorize(ll n) {
	if(check_prime(n)) return mxfac = max(mxfac, n), void();
	if(mxfac >= n) return; if(n <= 2) return;
	ll t; while((t = pollard_rho(n)) == n);
	factorize(t), factorize(n / t);
}

void solve() {
	n = lin; if(check_prime(n)) puts("Prime");
	else mxfac = 0, factorize(n), printf("%lld\n", mxfac);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	int T = in; while(T--) solve();
	return 0;
}
