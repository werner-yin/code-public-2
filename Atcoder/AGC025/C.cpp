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

int n, l[N], r[N];
ll ans, ret;
multiset < pii > sl, sr;

ll trans(int &pos, int id) {
	if(l[id] <= pos && pos <= r[id]) return 0;
	ll vt = 0;
	if(l[id] > pos) vt = l[id] - pos, pos = l[id];
	else vt = pos - r[id], pos = r[id];
	return vt;
}

void calc(int cur) {
	int lst = 0;
	rep(i, 1, n) {
		if(cur == 0) {
			pii v = *sr.rbegin(); sr.erase(--sr.end()); sl.erase(sl.find({ r[v.se], v.se }));
			ret += trans(lst, v.se);
		} else {
			pii v = *sl.begin(); sl.erase(sl.begin()); sr.erase(sr.find({ l[v.se], v.se }));
			ret += trans(lst, v.se);
		} cur ^= 1; //cerr << i << " " << lst << " " << ret << endl;
	} ret += abs(lst);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in; rep(i, 1, n) l[i] = in, r[i] = in;
	rep(i, 1, n) sl.ep(r[i], i), sr.ep(l[i], i);
	ret = 0; calc(0); chkmax(ans, ret);
	sl.clear(), sr.clear(); rep(i, 1, n) sl.ep(r[i], i), sr.ep(l[i], i);
	ret = 0; calc(1); chkmax(ans, ret);
	cout << ans << endl; return 0;
}
