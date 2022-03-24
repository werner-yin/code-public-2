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

const int N = 5e5 + 10;

int n, m, K;
int mu[N + 10], smu[N + 10], pri[N], pnum;
bool v[N];
int pk[N], tot;

void init(int l) {
	mu[1] = 1; rep(i, 2, l) {
		if(!v[i]) pri[++pnum] = i, mu[i] = -1;
		rep(j, 1, pnum) {
			if(pri[j] * i > l) break;
			v[pri[j] * i] = true; if(i % pri[j] == 0) { mu[pri[j] * i] = 0; break; }
			mu[pri[j] * i] = -mu[i];
		}
	} rep(i, 1, l) smu[i] = smu[i - 1] + mu[i];
}

unordered_map < int, ll > mp;

ll S(int x) {
	if(x < N - 10) return smu[x];
	if(mp.count(x)) return mp[x];
	ll res = 1;
	for(ll l = 2, r; l <= x; l = r + 1) {
		r = x / (x / l);
		res -= (r - l + 1) * S(x / l);
	} return mp[x] = res;
}

ll f(int n, int m, int k) {
	if(n == 0 || m == 0) return 0;
	if(k == 1) {
		ll res = 0;
		for(ll l = 1, r; l <= min(n, m); l = r + 1) {
			r = min(n / (n / l), m / (m / l));
			res += (S(r) - S(l - 1)) * (n / l) * (m / l);
		}
		return res;
	}
	ll res = 0;
	rep(_, 1, tot) {
		int d = pk[_]; if(k < d) break; if(k % d) continue; if(mu[d] == 0) continue;
		res += mu[d] * f(m / d, n, d);
	} return res;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in, m = in, K = in; init(N - 5);
	rep(d, 1, K) if(K % d == 0) pk[++tot] = d;
	printf("%lld\n", f(n, m, K));
	return 0;
}
