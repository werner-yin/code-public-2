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
ll tot;

bool solve(vec pot) {
	bool fl = 0; for(auto v : pot) fl |= v == 1;
	if(fl) {
		bool ret = 0; for(auto v : pot) ret ^= (v - 1) & 1;
		return ret;
	}
	int cnt = 0; for(auto v : pot) cnt += ~v & 1;
	if(cnt & 1) return true;
	if(cnt + 1 == pot.size()) {
		for(auto &v : pot) if(v & 1) v--;
		int ret = 0; for(auto v : pot) ret = __gcd(v, ret);
		for(auto &v : pot) v /= ret; return solve(pot) ^ 1;
	} else return false;
}

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in; vec pot; rep(i, 1, n) pot.eb(in);
	puts(solve(pot) ? "First" : "Second");
	return 0;
}
