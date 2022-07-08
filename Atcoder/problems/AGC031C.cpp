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

int n, a, b, c;

vec solve(int n, int a, int b) {
	if(n == 1) return { a, b };
	b ^= a; int pos = 0; rep(j, 0, n - 1) if(b >> j & 1) pos = j;
	b ^= 1 << pos; vec pot1 = solve(n - 1, 0, 1), pot2 = solve(n - 1, 1, b);
	for(auto v : pot2) v ^= 1 << n - 1, pot1.eb(v);
	for(auto &v : pot1) {
		if((v >> n - 1 & 1) ^ (v >> pos & 1)) {
			v ^= 1 << n - 1;
			v ^= 1 << pos;
		} v ^= a;
	}
	return pot1;
}

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in, a = in, b = in;
	c = a ^ b; if(__builtin_parity(c) != 1) return puts("NO"), 0;
	vec pot = solve(n, a, b);
	puts("YES"); for(auto v : pot) printf("%d ", v); puts("");
	return 0;
}
