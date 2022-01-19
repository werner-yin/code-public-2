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

const int N = 1e5 + 10;
const int mod = 1e9 + 7;
const int pri[] = { 2, 3, 5, 7, 11, 13, 31 };

int fa[N], n;
ll val[N];
int f[N];
vec G[N];

namespace sub1 {
	void dfs(int x, int p) {
		fa[x] = p;
		if(x == 1) f[x] = 1;
		else {
			for(int y = fa[x]; y; y = fa[y])
				if(val[y] % val[x] == 0) f[x] = (f[x] + f[y]) % mod;
		}
		for(auto y : G[x])
			if(y ^ p) dfs(y, x);
	}
	void solve() {
		dfs(1, 0); rep(i, 1, n) printf("%d\n", f[i]);
	}
}

namespace sub2 {
	mt19937 rnd(time(NULL));
	map < ll, int > cnt;
	ll mul(ll a, ll b, ll mod) { return (__int128) a * b % mod; }
	ll qp(ll x, ll t, ll mod) { ll res = 1; for(; t; t >>= 1, x = mul(x, x, mod)) if(t & 1) res = mul(res, x, mod); return res; }
	bool miller_rabin(ll n, ll a) {
		ll d = n - 1, ct = 0; while(~d & 1ll) d >>= 1, ct++;
		ll x = qp(a, d, n);
		rep(i, 1, ct) {
			if(x == 1 || x == n - 1) return true;
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
		ll v1 = 0, c = rnd() % (n - 1) + 1;
		for(int s = 1, t = 2; ; s <<= 1, t <<= 1) {
			ll v2 = v1, pro = 1, cnt = 0;
			rep(i, s + 1, t) {
				v2 = f(v2, c, n), pro = mul(pro, abs(v1 - v2), n), cnt++;
				if(cnt == 127) { cnt = 0; ll d = __gcd(n, pro); if(d > 1) return d; }
			} ll d = __gcd(n, pro); if(d > 1) return d; v1 = v2;
		}
	}
	void factorize(ll n) {
		if(n < 2) return; if(check_prime(n)) return cnt[n]++, void();
		ll t; while((t = pollard_rho(n)) == n); factorize(t), factorize(n / t); 
	}
	ll stk[N], ct[N], top;
	vector < ll > v1, v2;
	vec hav1[N * 10], hav2[N * 10];
	ll pv1[N], pv2[N];
	ll tot[510][510];
	void dfs(int x, int p) {
		::f[x] = x == 1;
		for(auto t : hav1[pv1[x]])
			::f[x] = (::f[x] + tot[t][pv2[x]]) % mod;
		for(auto t : hav2[pv2[x]])
			tot[pv1[x]][t] = (tot[pv1[x]][t] + ::f[x]) % mod;
		for(auto y : G[x]) if(y ^ p) dfs(y, x);
		for(auto t : hav2[pv2[x]])
			tot[pv1[x]][t] = (tot[pv1[x]][t] + mod - ::f[x]) % mod;
	}
	void solve() {
		factorize(val[1]);
		for(auto v : cnt) stk[++top] = v.fi, ct[top] = v.se;
		int op = -1; ll cost = val[1];
		rep(s, 0, (1 << top) - 1) {
			ll val1 = 1, val2 = 1;
			rep(i, 1, top)
				if(s >> i - 1 & 1) val1 *= ct[i] + 1;
				else val2 *= ct[i] + 1;
			if(max(val1, val2) <= cost) cost = max(val1, val2), op = s;
		}
		v1.eb(1); v2.eb(1);
		rep(i, 1, top) {	
			vector < ll > tv;
			ll pw = stk[i];
			rep(j, 1, ct[i]) {
				if(op >> i - 1 & 1) for(auto v : v1) tv.eb(v * pw);
				else for(auto v : v2) tv.eb(v * pw);
				pw *= stk[i];
			}
			if(op >> i - 1 & 1) for(auto v : tv) v1.eb(v);
			else for(auto v : tv) v2.eb(v);
		} sort(v1.begin(), v1.end()); sort(v2.begin(), v2.end());
		rep(i, 0, (int)v1.size() - 1) 
			rep(j, 0, i) if(v1[i] % v1[j] == 0) hav1[j].eb(i); // rever
		rep(i, 0, (int)v2.size() - 1)
			rep(j, 0, i) if(v2[i] % v2[j] == 0) hav2[i].eb(j); 
		
		rep(i, 1, n) {
			ll tv = val[i]; pv1[i] = pv2[i] = 1;
			rep(j, 1, top)
				if(tv % stk[j] == 0) {
					ll vv = 1;
					while(tv % stk[j] == 0) tv /= stk[j], vv *= stk[j];
					if(op >> j - 1 & 1) pv1[i] *= vv; else pv2[i] *= vv;
				}
			pv1[i] = lower_bound(v1.begin(), v1.end(), pv1[i]) - v1.begin();
			pv2[i] = lower_bound(v2.begin(), v2.end(), pv2[i]) - v2.begin();
		}
		dfs(1, 0); rep(i, 1, n) printf("%d\n", ::f[i]);
	}
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("walk.in", "r", stdin); freopen("walk.out", "w", stdout);
#endif
	n = in; rep(i, 1, n - 1) { int u = in, v = in; G[u].eb(v); G[v].eb(u); }
	rep(i, 1, n) val[i] = lin;
	if(0 && n <= 5000) sub1 :: solve();
	else sub2 :: solve();
	return 0;
}
