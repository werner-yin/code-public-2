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

int n;

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in;
	if(n == 3) { puts("2 5 63"); return 0; }
	vec pot, tpot;
	for(int cur = 1; cur + 5 <= 30000; cur += 6)
		pot.eb(cur + 1), tpot.eb(cur + 2), pot.eb(cur + 3), pot.eb(cur + 5);
	vec vpot;
	while(pot.size() > n - 2 || (n - pot.size()) & 1 ) vpot.eb(pot.back()), pot.pop_back();
	ll tot = 0; for(auto v : pot) tot += v;
	while(tot % 3 != 0) tot -= pot.back(), tot += vpot.back(), pot.pop_back(), pot.eb(vpot.back()), vpot.pop_back();
	while(pot.size() < n) pot.eb(tpot.back()), tpot.pop_back();
	//while(tot % 6 != 0) tot -= pot.back(), tot += tpot.back(), pot.pop_back(), pot.eb(tpot.back()), tpot.pop_back();
	tot = 0; for(auto v : pot) tot += v; assert(tot % 6 == 0);
	for(auto v : pot) printf("%d ", v); puts("");
	return 0;
}
