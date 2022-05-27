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

int n, m;
ll a, b;

map < pair < ll, ll >, bool > f;

bool dfs(ll a, ll b) {
	if(f.count({ a, b })) return f[{ a, b }]; if(b == 1 && (n - a) & 1) return true;
	bool ret = 0; 
	if(pow(a + 1, b) <= n) ret |= !dfs(a + 1, b); if(ret) return f[{ a, b }] = true;
	if(pow(a, b + 1) <= n) ret |= !dfs(a, b + 1);
	return f[{ a, b }] = ret;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in, m = in;
	while(m--) {
		a = in, b = in;
		while(pow(a + 1, b + 1) <= n) a++, b++;
		puts(dfs(a, b) ? "Yes" : "No");
	}
	return 0;
}
