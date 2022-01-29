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

int a[N], b[N], n;
pii t[N], mn[N];
vec ans1, ans2;

void out(vec a, vec b) {
	for(auto v : a) printf("%d ", v);
	for(auto v : b) printf("%d ", v);
}

bool vcheck() {
	int lst = ans2.front();
	for(auto v : ans2) {
		if(v == lst) continue;
		if(v > lst) return true;
		return false;
	} return false;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in; rep(i, 1, n) a[i] = in; rep(i, 1, n) b[i] = in, t[i] = { a[i], b[i] };
	mn[n + 1] = { 2e9, n + 1 }; per(i, n, 1) mn[i] = mn[i + 1], chkmin(mn[i], pii(a[i], i));
	int pos = 1; auto v = t[1];
	rep(i, 2, n) if(t[i] < v) pos = i, v = t[i];
	if(v.fi < v.se) {
		int pos = 0;
		rep(i, 1, n) if(t[i].fi == v.fi) ans1.eb(t[i].fi), ans2.eb(t[i].se), pos = i;
		bool chkfl = 0;
		rep(i, pos + 1, n) {
			auto nxt = mn[i]; //cerr << i << " " << nxt.se << endl;
			if(nxt.fi < *ans2.begin()) {
				ans1.eb(a[nxt.se]); ans2.eb(b[nxt.se]);
				i = nxt.se;
			} else if(nxt.fi == *ans2.begin()) {
				if(chkfl || (chkfl = vcheck())) ans1.eb(a[nxt.se]), ans2.eb(b[nxt.se]), i = nxt.se;
				else break;
			} else break;
		} out(ans1, ans2);
	} else printf("%d %d\n", v.fi, v.se);
	return 0;
}
