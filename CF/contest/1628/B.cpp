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

#define OK return puts("YES"), void()
#define GG return puts("NO"), void()

const int N = 1e6 + 10;

int n, f[310][310], mx[310];
string s[N];

bool check(string s) {
	auto t = s; reverse(t.begin(), t.end());
	return s == t;
}

void clear() {
	rep(i, 'a', 'z') rep(j, 'a', 'z') f[i][j] = 0, mx[i] = 0;
}

bool tsolve() { // 2 2 3, 3 2 2.
	clear();
	rep(i, 1, n)
		if(s[i].size() == 2) {
			int x = s[i][0], y = s[i][1];
			if(f[y][x]) return true;
			if(!f[x][y]) f[x][y] = i;
			mx[x] = i;
		} else if(s[i].size() == 3) { // xy z? zyx // xy zyx
			int x = s[i][2], y = s[i][1], z = s[i][0];
			if(f[x][y]) return true;
		}
	clear();
	per(i, n, 1)
		if(s[i].size() == 2) { 
			int x = s[i][0], y = s[i][1];
			if(!f[x][y]) f[x][y] = i;
			mx[y] = i;
		} else if(s[i].size() == 3) { // xyzyx
			int x = s[i][0], y = s[i][1], z = s[i][2];
			if(f[y][x]) return true;
		}
	return false;
}

void solve() {
	cin >> n; rep(i, 1, n) cin >> s[i];
	rep(i, 1, n) if(check(s[i])) OK; // simple
	map < string, bool > vis;
	rep(i, 1, n) vis[s[i]] = true;
	rep(i, 1, n) { // 11, 22, 33
		string t = s[i]; reverse(t.begin(), t.end());
		if(vis[t]) OK;
	}
	if(tsolve()) OK;
	GG;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	cin.tie(0);
	int T; cin >> T; for(; T; T--) solve();
	return 0;
}
