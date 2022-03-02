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

ll K, ans = 0, tans;
int n, a[N];
vec pot;
bool vis[N];

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in; K = lin; rep(i, 0, n - 1) a[i] = in;
	int x = 0;
	while(!vis[x]) vis[x] = true, pot.eb(x), x = (x + a[x]) % n, tans += a[x];
	//	assert(tans % n == 0);
	//cerr << x << " " << tans % n << endl;
	reverse(pot.begin(), pot.end());
	while(pot.back() != x && K) K--, ans += a[pot.back()], tans -= a[pot.back()], pot.pop_back();
	//cerr << tans % n << endl;
	reverse(pot.begin(), pot.end());
	//for(auto v : pot) cerr << v << " "; cerr << endl;
	tans = 0;
	for(auto v : pot) tans += a[v];
	//ll tmp = 0; for(auto v : pot) tmp = (tmp + a[v]) % n;
	//cerr << tmp << endl;
	ans += tans * (K / pot.size());  
	K %= pot.size(); //x = pot.back(); cerr << K << endl;
	while(K--) ans += a[x], x = (x + a[x]) % n;
	cout << ans << endl;
	return 0;
}
