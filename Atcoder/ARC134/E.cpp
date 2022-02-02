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

const int N = 210;
const int mod = 998244353;
const int B = 15;

int n, a[N];

map < vec, bool > res;

bool check(vec pot) {
	sort(pot.begin(), pot.end()); pot.resize(unique(pot.begin(), pot.end()) - pot.begin());
	if(pot.size() == 0) return 0; if(pot == vec{ 4, 8 }) return 1;
	if(pot == vec{ 1 }) return 1; if(pot == vec{ 2 }) return 1;
	for(auto v : pot) if(v % 12) return 0;
	if(res.count(pot)) return res[pot];
	int mx = pot.back();
	rep(i, 1, mx) {
		vec pp;
		for(auto v : pot) if(v % i) pp.eb(v % i);
		if(check(pp)) return res[pot] = 0;
	} return res[pot] = 1;
}

int calc(vec pot) {
	vec f(1 << pot.size(), 0); f[0] = 1;
	rep(i, 1, n) {
		vec g(f.size(), 0); 
		rep(j, 0, pot.size() - 1) if(a[i] >= pot[j]) {
			rep(s, 0, f.size() - 1) if(f[s]) {
				(g[s | 1 << j] += f[s]) %= mod;
			}
		} f.swap(g);
	} return f.back();
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in; rep(i, 1, n) a[i] = in;
	vector < vec > fail;
	fail.eb(vec{ 1 }); fail.eb(vec{ 2 }); fail.eb(vec{ 4, 8 });
	rep(s, 0, (1 << B + 1) - 1) {
		vec pot;
		rep(i, 0, B) if(s >> i & 1) pot.eb((i + 1) * 12);
		if(check(pot)) fail.eb(pot);
		cerr << s << endl;
	} 
	int ans = 1; rep(i, 1, n) ans = 1ll * ans * a[i] % mod;
	for(auto v : fail) ans = (ans + mod - calc(v)) % mod;
	cout << ans << endl;
	return 0;
}