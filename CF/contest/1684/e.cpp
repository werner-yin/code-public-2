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

int n, K, a[N];
map < int, int > cnt, lcnt;

void solve() {
	n = in, K = in; cnt.clear(); rep(i, 1, n) a[i] = in, cnt[a[i]]++;
	int ans = 1e9; set < pii > s; for(auto v : cnt) s.ep(v.se, v.fi);
	lcnt = cnt;
	rep(mex, 0, n + 2) {
		chkmin(ans, (int)s.size());
		if(lcnt[mex]) {
			int t = lcnt[mex] - cnt[mex];
			if(cnt[mex]) s.erase({ cnt[mex], mex });
			while(t-- && s.size()) {
				auto it = s.begin();
				auto v = *it; s.erase(it);
				v.fi--; cnt[v.se]--; if(v.fi) s.insert(v);
			} 
			continue;
		}
		//cerr << mex << " " << s.size() << endl;
		//for(auto v : s) cerr << v.fi << " " << v.se << endl;
		//cerr << endl;
		if(K && s.size()) {
			auto it = s.begin();
			auto v = *it; s.erase(it);
			v.fi--; cnt[v.se]--; if(v.fi) s.insert(v); K--;
		} else break;
	} cout << ans << endl;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	for(int T = in; T; T--) solve(); return 0;
}
