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

int n, a[N], ans;
map < int, int > stu, p;

int calc() { return max(a[1], 0) + max(a[2], 0) + max(a[3], 0); }

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in; rep(i, 1, n) { int x = in, y = in; p[y] ^= 1, stu[x] ^= 1 << y % 3; }
	for(auto v : stu) {
		if(v.se != 0 && v.se != 1 && v.se != 2 && v.se != 4) v.se ^= 7;
		a[v.se == 1 ? 1 : v.se == 2 ? 2 : v.se == 4 ? 3 : 0]++;
	}
	for(auto v : p) if(v.se) a[v.fi % 3 + 1]--, ans++;
	int lst = calc();
	while(true) {
		sort(a + 1, a + 4); a[1]++, a[2]++, a[3]--; if(calc() >= lst) { a[1]--, a[2]--, a[3]++; break; }
		lst = calc();
	}
	if(a[1] & 1) a[1]++, a[2]++, a[3]--; cout << ans + calc() << endl; return 0;
}
