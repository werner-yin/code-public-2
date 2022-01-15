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
const int V = 1e6;

int n, a[N], cnt[N], pri[N], pnum, mu[N];
ll res1[N], res2[N];
bool v[N];

void shai(int l) {
	mu[1] = 1;
	rep(i, 2, l) {
		if(!v[i]) pri[++pnum] = i, mu[i] = -1;
		rep(j, 1, pnum) {
			if(pri[j] * i > l) break;
			v[pri[j] * i] = true; if(i % pri[j] == 0) { mu[pri[j] * i] = 0; break; }
			mu[pri[j] * i] = -mu[i];
		}
	}
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in;
	rep(i, 1, n) a[i] = in, cnt[a[i]]++;
	shai(1000000); int ans = 0;
	per(i, V, 1) {
		if(cnt[i]) {
			res1[i] = res2[i] = cnt[i];
		} else {
			ll tot = 0;
			rep(j, i, V) {
				ll t1 = 0, t2 = 0;
				rep(k, j, V) {
					t1 += res1[k];
					t2 += res2[k];
					k += j - 1;
				}
				tot += (t1 * t1 - t2) * mu[j / i];
				j += i - 1;
			} if(tot) { /*cerr << "!" << i << " " << tot << endl;*/ res1[i] = res2[i] = 1; ans++; }
		}
	} cout << ans << endl;
	return 0;
}
