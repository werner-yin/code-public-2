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

int n, K;
string s[100];
int cnt[300];

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in, K = in;
	rep(i, 0, n - 1) cin >> s[i];
	int ans = 0;
	rep(i, 0, (1 << n) - 1) {
		rep(j, 'a', 'z') cnt[j] = 0;
		rep(j, 0, n - 1) if(i >> j & 1) {
			for(auto v : s[j]) cnt[v]++;
		}
		int t = 0;
		rep(j, 'a', 'z') t += cnt[j] == K;
		chkmax(ans, t);
	} cout << ans << endl;
	return 0;
}
