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

int n, c[N];
int cnt[N];

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in; rep(i, 1, 9) c[i] = in;
	int mn = c[9], p = 9;
	per(i, 9, 1) if(c[i] < mn) mn = c[i], p = i;
	cnt[p] += n / c[p]; n %= c[p];
	per(i, 9, p + 1) {
		int t = c[i] - c[p], v = n / t;
		cnt[i] += v, cnt[p] -= v, n %= t;
	}
	per(i, 9, 1) 
		while(cnt[i] --> 0) putchar(i + '0');
	puts("");
	return 0;
}
