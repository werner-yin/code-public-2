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
const int inf = 1e9;

int n, K, Q;
int tx[N], tot, ans[N], qtot, pv[N], ntx[N];
struct node {
	int op, tim, pos, tp;
	node(int a = 0, int b = 0, int c = 0, int d = 0) : op(a), tim(b), pos(c), tp(d) {}
} q[N];
int val[N << 2];
multiset < int > tpos[N], ttpos;
void pu(int o) { val[o] = min(val[o << 1], val[o << 1 | 1]); }
void build(int o = 1, int l = 1, int r = tot) {
	if(l == r) return val[o] = inf, void(); int mid = l + r >> 1;
	build(o << 1, l, mid); build(o << 1 | 1, mid + 1, r); pu(o);
}
//namespace T {
void upd(int pos, int v, int o = 1, int l = 1, int r = tot) {
	if(l == r) return val[o] = v, void(); int mid = l + r >> 1;
	if(pos <= mid) upd(pos, v, o << 1, l, mid); else upd(pos, v, o << 1 | 1, mid + 1, r); pu(o);
}
	//}
//void upd(int pos, int v) { cerr << "U: " << pos << " " << v << endl; T :: upd(pos, v); }

int query(int p, int tmn, int o = 1, int l = 1, int r = tot) {
	if(l == r) return l; int mid = l + r >> 1;
	if(p <= mid && min(val[o << 1 | 1], tmn) >= 2 * tx[p] - tx[mid + 1]) return query(p, min(tmn, val[o << 1 | 1]), o << 1, l, mid);
	else return query(p, tmn, o << 1 | 1, mid + 1, r);
}
int get(int p, int o = 1, int l = 1, int r = tot) {
	if(l == r) return val[o]; int mid = l + r >> 1;
	return p <= mid ? min(get(p, o << 1, l, mid), val[o << 1 | 1]) : get(p, o << 1 | 1, mid + 1, r);
}

void del(int tp, int pos) {
	//cerr << "E: " << tp << " " << pos << endl;
	ttpos.erase(ttpos.find(tx[*tpos[tp].rbegin()]));
	auto it = tpos[tp].find(pos); tpos[tp].erase(it++);
	if(it != tpos[tp].end()) upd(*it, it == tpos[tp].begin() ? -inf : tx[*prev(it)]);
	upd(pos, inf);
	ttpos.insert(!tpos[tp].size() ? -inf : tx[*tpos[tp].rbegin()]); upd(tot, *ttpos.begin());
}
void add(int tp, int pos) {
	//cerr << "A: " << tp << " " << pos << endl;
	ttpos.erase(ttpos.find(!tpos[tp].size() ? -inf : tx[*tpos[tp].rbegin()]));
	tpos[tp].insert(pos); auto it = tpos[tp].find(pos);
	if(next(it) != tpos[tp].end()) upd(*next(it), tx[*it]);
	upd(*it, it == tpos[tp].begin() ? -inf : tx[*prev(it)]);
	ttpos.insert(tx[*tpos[tp].rbegin()]); upd(tot, *ttpos.begin());
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in, K = in, Q = in;
	rep(i, 1, n) {
		int x = in, t = in, a = in, b = in;
		q[++qtot] = node(0, a, x, t); q[++qtot] = node(-1, b + 1, x, t);
		tx[++tot] = x;
	}
	rep(i, 1, Q) {
		int x = in, t = in;
		q[++qtot] = node(i, t, x);
		tx[++tot] = x;
	}
	tx[++tot] = inf; sort(tx + 1, tx + tot + 1); rep(i, 1, tot) pv[i] = i;//tot = unique(tx + 1, tx + tot + 1) - tx - 1;
	per(i, tot, 1) ntx[i] = tx[i] == tx[i + 1] ? ntx[i + 1] : tx[i + 1];
	rep(i, 1, n) q[i * 2].pos = q[i * 2 - 1].pos = pv[lower_bound(tx + 1, tx + tot + 1, q[i * 2].pos) - tx]++;
	rep(i, 2 * n + 1, qtot) q[i].pos = pv[lower_bound(tx + 1, tx + tot + 1, q[i].pos) - tx]++;
	rep(i, 1, K) ttpos.ep(-inf); build(); 
	sort(q + 1, q + qtot + 1, [&](auto a, auto b) { return a.tim ^ b.tim ? a.tim < b.tim : a.op < b.op; });
	rep(i, 1, qtot)
		if(q[i].op == -1) del(q[i].tp, q[i].pos);
		else if(q[i].op == 0) add(q[i].tp, q[i].pos);
		else {
			if(*ttpos.begin() < 0) ans[q[i].op] = -1;
			else {
				/*
				per(t, tot, 1) {
					int v = get(t);
					//cerr << v << " " << tx[q[i].pos] * 2 - tx[t] << " " << t << endl;
					if(v >= tx[q[i].pos] * 2 - tx[t]) { ans[q[i].op] = tx[t] - tx[q[i].pos]; }
					else { ans[q[i].op] = max(tx[t] - tx[q[i].pos], tx[q[i].pos] - get(t + 1)); break; }
				}
				continue;*/
				int p = query(q[i].pos, inf);
				//	cerr << "!" << p << " " << tx[p + 1] << endl;
				ans[q[i].op] = max(tx[p] - tx[q[i].pos], tx[q[i].pos] - get(p + 1));
			}
		}
	rep(i, 1, Q) printf("%d\n", ans[i]); return 0;
}
