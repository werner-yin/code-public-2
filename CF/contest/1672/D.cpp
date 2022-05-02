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

queue < int > a, b;
multiset < int > s;

void solve() {
	n = in; while(a.size()) a.pop(); while(b.size()) b.pop(); s.clear();
	rep(i, 1, n) a.push(in); rep(i, 1, n) b.push(in);
	while(a.size() && b.size()) {
		if(a.front() == b.front()) {
			int x = a.front(); a.pop(), b.pop();
			while(b.size() && b.front() == x && s.find(b.front()) != s.end()) s.erase(s.find(b.front())), b.pop();
		} else s.insert(a.front()), a.pop();
	} if(a.size() || b.size()) puts("NO"); else puts("YES");
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	for(int T = in; T; T--) solve();
	return 0;
}
