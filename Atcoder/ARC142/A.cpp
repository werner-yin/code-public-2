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

ll n, K;
vector < ll > pot;

ll rev(ll x) {
	vec pot; while(x > 0) pot.eb(x % 10), x /= 10;
	ll t = 0; for(auto v : pot) t = t * 10 + v;
	return t;
}

void get(ll x) {
	while(x <= n) pot.eb(x), x *= 10;
}

ll reduce(ll x) { while(x % 10 == 0) x /= 10; return x; }

ll tget(ll x) {
	x = reduce(x); ll a = x, b = rev(x);
	//	cerr << x << " "<< min(a, b) << endl;
	return min(a, b); 
}

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = lin, K = lin; get(K); get(rev(K));
	sort(pot.begin(), pot.end());
	pot.resize(unique(pot.begin(), pot.end()) - pot.begin());
	ll ans = 0;
	for(auto v : pot) if(tget(v) == K) ans++;
	//for(auto v : pot) cerr << v << " ";
	cout << ans << endl;
	return 0;
}
