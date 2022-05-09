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

int n, c[N], q[N], id[N], rt[N], tim, ans[N];

mt19937_64 rnd(19491001);

namespace tr {
	const int T = 2.5e7 + 10;
	struct node {
		int ch[2], tvis, val;
		ll len, siz, ad;
	} val[T];
	int ndn;
	void pu(int x) { val[x].siz = val[val[x].ch[0]].siz + val[val[x].ch[1]].siz + val[x].len; }
	int nd(int v, int tv) { int x = ++ndn; val[x].len = v, val[x].val = tv; pu(x); return x; }
	int copy(int y) { if(val[y].tvis == tim) return y; int x = ++ndn; val[x] = val[y]; val[x].tvis = tim; pu(x); return x; }
	void pt(int &x, ll v) { if(!x) return; x = copy(x); val[x].val += v; val[x].ad += v; }
	void pd(int &x) { if(!x) return; x = copy(x); if(val[x].ad) pt(val[x].ch[0], val[x].ad), pt(val[x].ch[1], val[x].ad), val[x].ad = 0; }
	int merge(int x, int y) {
		if(!x || !y) return x | y; pd(x), pd(y); if(val[x].siz + val[y].siz == 0) { puts("0000!"), exit(0); }
		if(rnd() % (val[x].siz + val[y].siz) < val[x].siz) return val[x].ch[1] = merge(val[x].ch[1], y), pu(x), x;
		else return val[y].ch[0] = merge(x, val[y].ch[0]), pu(y), y;
	}
	void split(int cur, ll k, int &x, int &y) {
		if(!cur) return x = y = 0, void(); pd(cur);
		if(val[val[cur].ch[0]].siz + val[cur].len <= k)
			x = cur, split(val[cur].ch[1], k - val[val[cur].ch[0]].siz - val[cur].len, val[x].ch[1], y), pu(x);
		else if(val[val[cur].ch[0]].siz == k)
			x = copy(val[cur].ch[0]), y = cur, val[y].ch[0] = 0, pu(x), pu(y);
		else if(val[val[cur].ch[0]].siz <= k)
			x = nd(k - val[val[cur].ch[0]].siz, val[cur].val), y = cur, val[y].len = val[cur].len - val[x].len,
				val[x].ch[0] = val[cur].ch[0], val[y].ch[0] = 0, pu(x), pu(y);
		else 
			y = cur, split(val[cur].ch[0], k, x, val[y].ch[0]), pu(y);
	}
}

using namespace tr;

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in; rep(i, 1, n) c[i] = in, q[i] = in, id[i] = i;
	sort(id + 1, id + n + 1, [&](int x, int y) { return q[x] ^ q[y] ? q[x] < q[y] : c[x] > c[y]; });
	int a, b; rt[0] = nd(1e9 + 7, 0);
	rep(i, 1, n) {
		int x = id[i]; rt[i] = rt[i - 1]; tim = i;
		split(rt[i], c[x], a, b); pt(rt[i - 1], 1); rt[i] = merge(a, rt[i - 1]);
	} 
	int m = in, c;
	auto query = [&](int t) {
					 split(rt[n], t, a, b); split(b, 1, b, c);
					 int ans = val[b].val; rt[n] = merge(a, merge(b, c));
					 return ans;
				 };
	rep(i, 1, m) printf("%d ", query(in)); puts("");
	return 0;
}
