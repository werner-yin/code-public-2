#include <bits/stdc++.h>

#define in read<int>()
#define rep(i, x, y) for(int i = (x); i <= (y); i++)
#define per(i, x, y) for(int i = (x); i >= (y); i--)

using namespace std;

using ll = long long;

template < typename T > T read() {
	T x = 0; bool f = 0; char ch = getchar();
	while(!isdigit(ch)) f |= ch == '-', ch = getchar();
	while(isdigit(ch)) x = x * 10 + (ch ^ 48), ch = getchar();
	return f ? -x : x;
}

const int N = 1e8 + 10;

int n, m, K;
int mu[N], pri[N], pnum;
bool v[N];

void init(int l) {
	mu[1] = 1; rep(i, 2, l) {
		if(!v[i]) pri[++pnum] = i, mu[i] = -1;
		rep(j, 1, pnum) {
			if(pri[j] * i > l) break;
			v[pri[j] * i] = true; if(i % pri[j] == 0) { mu[pri[j] * i] = 0; break; }
			mu[pri[j] * i] = -mu[i];
		}
	}
}

ll lcm(ll x, ll y) { return x / __gcd(x, y) * y; }

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in, m = in, K = in;
	init(max(n, K));
	ll ans = 0;
	//rep(j, 1, m) { if(__gcd(j, K) == 1) rep(i, 1, n) if(__gcd(i, j) == 1) ans++; }
	rep(d1, 1, K) 
		if(K % d1 == 0 && mu[d1]) {
			ll res = 0;
			rep(d2, 1, n) if(mu[d2]) {
				ll t = 1ll * (m / lcm(d1, d2)) * (n / d2) * mu[d2];
				res += t;
			} ans += res * mu[d1];
		}
	printf("%lld\n", ans);
	return 0;
}
