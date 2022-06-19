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

int a[600][600], id[N];
vec tpot[N];
int n;

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in;
	vec pot1, pot2;
	rep(i, 1, n) if(i <= (n + 1) / 2) pot1.eb(i); else pot2.eb(i);
	int lst = 1;
	rep(i, 1, n * n) {
		if(tpot[lst].size() == n) lst++;
		tpot[lst].eb(i);
	}
	rep(i, 1, n) {
		int x = 0;
		if(pot1.size() > pot2.size()) {
			x = pot1.back();
			pot1.pop_back();
		} else {
			x = pot2.back();
			pot2.pop_back();
		}
		for(auto v : tpot[x]) printf("%d ", v); puts("");
	}
	return 0;
}
