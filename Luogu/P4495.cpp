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

int n, q, P, f[N], cnt[N], ans[N], pot[N], tot, pw[N];
unordered_map < int, int > ind;

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in, q = in, P = in;
	rep(i, 1, P) {
		if(i * i > P) break; if(P % i) continue;
		pot[++tot] = i; if(i * i != P) pot[++tot] = P / i;
	}
	sort(pot + 1, pot + tot + 1); rep(i, 1, tot) ind[pot[i]] = i;
	rep(i, 1, n) {
		int v = in;
		cnt[ind[__gcd(v, P)]]++;
	} pw[0] = 1; rep(i, 1, n) pw[i] = pw[i - 1] * 2ll % mod;
	f[ind[P]] = 1;
	rep(i, 1, tot) rep(j, 1, tot) {
		int k = ind[__gcd(pot[i], pot[j])];
		f[k] = (f[k] + 1ll * f[j] * (pw[cnt[i]] - 1) % mod) % mod;
	}
	rep(i, 1, tot) rep(j, 1, i) if(pot[i] % pot[j] == 0) ans[i] = (ans[i] + f[j]) % mod;
	rep(i, 1, q) printf("%d\n", ans[ind[__gcd(in, P)]]);
	return 0;
}
