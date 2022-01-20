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

const int N = 210;

vector < int > pot[N];
int n, cnt[N], ban[N], pos[N], ans[N], ind[N];

void calc() {
	rep(j, 1, n) cnt[j] = pos[j] = 0;
	rep(j, 1, n - 1)
		if(!ban[j]) {
			for(auto v : pot[j]) cnt[v]++, pos[v] = j;
		}
}

bool solve(int fl) {
	rep(i, 1, n) ans[i] = 0, ban[i] = false;
	calc(); int lfp = 0;
	per(i, n, 2) {
		calc();
		
		if(!lfp) {
			int fp = 0, tp = 0;
			rep(i, 1, n) {
				if(cnt[i] == 1) fp = tp, tp = i;
			}
			bool tl = false;
			if(fp && tp) tl = true;
			if(fl) swap(fp, tp);
			if(tl && fp) lfp = fp;
		}
		
		int pos = 0;
		rep(j, 1, n) if((lfp == 0 || j != lfp) && cnt[j] == 1) {
			pos = j; ban[::pos[j]] = true; break;
		}
		if(pos == 0) return false; ans[i] = pos;
	} rep(i, 1, n) cnt[i] = 0;
	rep(i, 2, n) cnt[ans[i]]++;
	rep(i, 1, n) if(!cnt[i]) ans[1] = i;
	rep(i, 1, n) ind[ans[i]] = i;
	rep(i, 1, n - 1) {
		int xl = n, xr = 1;
		for(auto v : pot[i]) chkmin(xl, ind[v]), chkmax(xr, ind[v]);
		if(xr - xl + 1 == pot[i].size()) continue;
		return false;
	}
	rep(i, 1, n) printf("%d ", ans[i]);
	puts(""); return true;
}

void solve() {
	n = in; rep(i, 1, n) ans[i] = false;
	rep(i, 1, n - 1) {
		int k = in; pot[i].clear();
		while(k--) pot[i].eb(in);
	}
	if(solve(0)) return;
	if(solve(1)) return;
	puts("-1"); 
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	for(int T = in; T; T--) solve();
	return 0;
}
