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

int n, c[N], q[N], id[N], ans[N], m;

mt19937_64 rnd(19491001);

namespace tr {
	int ch[N][2], val[N], ret[N], siz[N], ad1[N], ad2[N], ndn;
	int nd(int v) { int x = ++ndn; val[x] = v; siz[x] = 1; ret[x] = 0; return x; }
	void pu(int x) { siz[x] = siz[ch[x][0]] + siz[ch[x][1]] + 1; }
	void pt(int x, int v, int tv) { ad1[x] += v, ad2[x] += tv, val[x] += v, ret[x] += tv; }
	void pd(int x) {
		pt(ch[x][0], ad1[x], ad2[x]), pt(ch[x][1], ad1[x], ad2[x]), ad1[x] = ad2[x] = 0;
	}
	int merge(int x, int y) {
		if(!x || !y) return x | y; pd(x), pd(y);
		if(rnd() % (siz[x] + siz[y]) < siz[x]) return ch[x][1] = merge(ch[x][1], y), pu(x), x;
		else return ch[y][0] = merge(x, ch[y][0]), pu(y), y;
	}
	void split(int cur, int k, int &x, int &y) {
		if(!cur) return x = y = 0, void(); pd(cur);
		if(val[cur] <= k) x = cur, split(ch[cur][1], k, ch[x][1], y), pu(x);
		else y = cur, split(ch[cur][0], k, x, ch[y][0]), pu(y);
	}
	void expand(int x, vec &pot) {
		if(!x) return; pot.eb(x); pd(x); expand(ch[x][0], pot); expand(ch[x][1], pot); ch[x][0] = ch[x][1] = 0; pu(x);
	}
	int ins(int x, int v) {
		int a, b; split(x, val[v], a, b); 
		x = merge(a, merge(v, b)); return x;
	}
	void getall(int x) {
		if(!x) return; pd(x); getall(ch[x][0]); getall(ch[x][1]);
	}
}

using namespace tr;

int rt;
vec pot;

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in; rep(i, 1, n) c[i] = in, q[i] = in, id[i] = i;
	sort(id + 1, id + n + 1, [&](int x, int y) { return q[x] ^ q[y] ? q[x] > q[y] : c[x] < c[y]; });
	m = in; rep(i, 1, m) rt = ins(rt, nd(in));
	int a, b, d, e;
	rep(i, 1, n) {
		int x = id[i]; split(rt, c[x] - 1, a, b), split(b, c[x] * 2, d, e);
		pot.clear(); expand(d, pot); rt = a; for(auto v : pot) val[v] -= c[x], ret[v]++, rt = ins(rt, v);
		pt(e, -c[x], 1), rt = merge(rt, e); 
	} getall(rt); 
	rep(i, 1, m) printf("%d ", ret[i]); puts("");
	return 0;
}
