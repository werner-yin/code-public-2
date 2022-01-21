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
const db inf = 1e9;
const db eps = 1e-11;

int n, T, Q, p[N], l[N], cho[N];
db ans;

struct cmp {
	bool operator ()(pair < db, pii > a, pair < db, pii > b) {
		return fabs(a.fi - b.fi) > eps ? a.fi < b.fi : a.se.fi ^ b.se.fi ? a.se.fi < b.se.fi : a.se.se < b.se.se;
	}
};
	
set < pair < db, pii > > s, t;

db calc(int x, int c) { return 1. * p[x] * (min(c, l[x])) / (l[x] + min(c, l[x])) ; }
pair < db, pii > tcalc(int x, int c) { return pair < db, pii >(c == 0 ? inf : calc(x, c) - calc(x, c - 1), pii(x, c)); }

void add() {
	auto it = s.rbegin();
	ans += it->fi; int x, c; tie(x, c) = it->se; cho[x] = c;
	t.erase(tcalc(x, c - 1)); t.insert(*it); s.erase(*it); s.insert(tcalc(x, c + 1));
	//cerr <<"!" <<  t.size() << " " << s.size() <<endl;
}
void del() {
	auto it = t.begin(); assert(t.begin() != t.end());
	ans -= it->fi; int x, c; tie(x, c) = it->se; cho[x] = c - 1;
	//cerr << " P : " << s.size() << " " << t.size() << endl;
	s.erase(tcalc(x, c + 1)); s.insert(*it);
	t.erase(*it); t.insert(tcalc(x, c - 1));
	//cerr << s.size() << " " << t.size() << endl;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in, T = in, Q = in;
	rep(i, 1, n) p[i] = in;
	rep(i, 1, n) l[i] = in;
	rep(i, 1, n) s.ep(tcalc(i, 1)), t.ep(tcalc(i, 0));
	while(T--) add();
	while(Q--) {
		int tp = in, x = in;
		s.erase(tcalc(x, cho[x] + 1)); t.erase(tcalc(x, cho[x])); ans -= calc(x, cho[x]) - calc(x, 0);
		if(tp == 1) l[x]++; else l[x]--;
		s.insert(tcalc(x, cho[x] + 1)); t.insert(tcalc(x, cho[x])); ans += calc(x, cho[x]) - calc(x, 0);
		while(s.rbegin()->fi > t.begin()->fi) del(), add();
		printf("%.7lf\n", ans);
	}
	return 0;
}
