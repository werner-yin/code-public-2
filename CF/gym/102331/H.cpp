#include <bits/stdc++.h>

#define eb emplace_back
#define in read<int>()
#define rep(i, x, y) for(int i = (x); i <= (y); i++)
#define per(i, x, y) for(int i = (x); i >= (y); i--)

using namespace std;

using ll = long long;
using pii = pair < int, int >;
using vec = vector < int >;
using veg = vector < pii >;

template < typename T > T read() {
	T x = 0; bool f = 0; char ch = getchar();
	while(!isdigit(ch)) f |= ch == '-', ch = getchar();
	while(isdigit(ch)) x = x * 10 + (ch ^ 48), ch = getchar();
	return f ? -x : x;
}

const int N = 5e4 + 10;
const int inf = 0x3f3f3f3f;

vec pot[N << 2][2][2];
int pos[N << 2][2][2], n, m, a[N];

void merge(const vec &a, const vec &b, vec &c) {
	const int *ia = a.data() + 1, *ib = b.data() + 1, *ea = a.data() + a.size(), *eb = b.data() + b.size();
	c.resize(a.size() + b.size() - 1);
	int *ic = c.data(); int ca = a[0], cb = b[0];
	while(ia != ea || ib != eb) {
		*ic = ca == -inf || cb == -inf ? -inf : ca + cb; ic++;
		if(ia != ea && (ib == eb || *ia - ca > *ib - cb)) ca = *ia, ia++;
		else cb = *ib, ib++;
	} *ic = ca == -inf || cb == -inf ? -inf : ca + cb;
}
void shift(const vec &a, vec &b) {
	rep(i, 1, a.size() - 1) b[i - 1] = max(a[i], b[i - 1]);
} vec ret;
void build(int o = 1, int l = 1, int r = n) {
	if(l == r) {
		pot[o][0][1] = pot[o][1][0] = pot[o][1][1] = { -inf, a[l] };
		pot[o][0][0] = { 0, a[l] }; return;
	} int mid = l + r >> 1; build(o << 1, l, mid); build(o << 1 | 1, mid + 1, r);
	rep(x, 0, 1) rep(y, 0, 1) {
		merge(pot[o << 1][x][0], pot[o << 1 | 1][0][y], pot[o][x][y]);
		merge(pot[o << 1][x][1], pot[o << 1 | 1][1][y], ret);
		shift(ret, pot[o][x][y]);
		//cerr << pot[o][x][y].size() << endl;
	}
}

ll ares[2], atot[2], tk;
ll nres[2], ntot[2];

void ask(int xl, int xr, int o = 1, int l = 1, int r = n) {
	if(xl <= l && r <= xr) {
		nres[0] = nres[1] = -0x3f3f3f3f3f3f3f3f; ntot[0] = ntot[1] = 0;
		rep(x, 0, 1) rep(y, 0, 1) {
			int &pos = ::pos[o][x][y]; //cerr << pos << endl;
			while(pos + 1 < pot[o][x][y].size() && pot[o][x][y][pos + 1] - pot[o][x][y][pos] > tk) pos++;
			//cerr << pos << endl; cerr << pot[o][x][y].size() << endl;
			if(pot[o][x][y][pos] == -inf) continue;
			ll val = pot[o][x][y][pos] - (pos - (x == 1)) * tk + ares[x];
			if(val > nres[y] || (val == nres[y] && pos + atot[x] - (x == 1) <= ntot[y]))
				ntot[y] = pos + atot[x] - (x == 1),
					nres[y] = val;
		} ares[0] = nres[0]; ares[1] = nres[1]; atot[0] = ntot[0]; atot[1] = ntot[1];
		return;
	} int mid = l + r >> 1;
	if(xl <= mid) ask(xl, xr, o << 1, l, mid); if(xr > mid) ask(xl, xr, o << 1 | 1, mid + 1, r);
}

int tid, nid;
int cl[N], cr[N], nl[N], nr[N];
int l[N], r[N], K[N], ctot[N];
ll ans[N];
vec vp[N], np[N];

int main() {
#ifndef ONLINE_JUDGE
	freopen("rated.in", "r", stdin); freopen("rated.out", "w", stdout);
#endif
	n = in, m = in; rep(i, 1, n) a[i] = in; rep(i, 1, m) l[i] = in, r[i] = in, K[i] = in, vp[1].eb(i);
	build(); tid = 1; cl[1] = - 100 * N; cr[1] = 100 * N;
	while(tid) {
		nid = 0;
		rep(i, 1, n << 2) pos[i][0][0] = pos[i][0][1] = pos[i][1][0] = pos[i][1][1] = 0;
		per(i, tid, 1) {
			if(cl[i] == cr[i]) {
				for(auto v : vp[i]) {
					ares[0] = 0; ares[1] = -0x3f3f3f3f3f3f3f3f; atot[0] = atot[1] = 0;
					tk = cl[i]; ask(l[v], r[v]); ans[v] = ares[0] + tk * K[v];
					//cerr << cl[i] << " " << cr[i] << " " << v << endl;
				} vp[i].clear();
			} else {
				for(auto v : vp[i]) {
					tk = cl[i] + cr[i] >> 1;
					ares[0] = 0; ares[1] = -0x3f3f3f3f3f3f3f3f; atot[0] = atot[1] = 0;
					ask(l[v], r[v]); ctot[v] = atot[0];
				}
			}
		}
		rep(i, 1, tid) if(vp[i].size()) {
			tk = (cl[i] + cr[i]) >> 1;
			vec pot1, pot2;
			for(auto v : vp[i]) {
				if(ctot[v] > K[v]) pot2.eb(v);
				else pot1.eb(v);
			} vec().swap(vp[i]);
			if(pot1.size()) np[++nid] = pot1, nl[nid] = cl[i], nr[nid] = tk;
			if(pot2.size()) np[++nid] = pot2, nl[nid] = tk + 1, nr[nid] = cr[i];
		}
		rep(i, 1, nid) vp[i] = np[i], vec().swap(np[i]), cl[i] = nl[i], cr[i] = nr[i];
		tid = nid;
	} rep(i, 1, m) printf("%lld\n", ans[i]);
	return 0;
}

