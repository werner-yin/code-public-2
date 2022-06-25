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
const int M = 1e7 + 10;

int ndn, n, a[N], id[N], ind[N], tot, tim, dfn[N], R[N];
int dis[N], stk[N], top, l1[N], l2[N], r1[N], r2[N];

int fa[N];
pii mx[21][N], mn[21][N];
int lg[N];

pii getmx(int x, int y) {
	int k = y - x + 1; k = lg[k];
	return max(mx[k][x], mx[k][y - (1 << k) + 1]);
}

pii getmn(int x, int y) {
	int k = y - x + 1; k = lg[k];
	return min(mn[k][x], mn[k][y - (1 << k)  + 1]);
}

void solve() {
	n = in; rep(i, 1, n) a[i] = in;
	rep(i, 2, n) lg[i] = lg[i >> 1] + 1;
	rep(i, 1, n) mx[0][i] = mn[0][i] = { a[i], i };
	rep(j, 1, lg[n])
		rep(i, 1, n - (1 << j) + 1)
		mx[j][i] = max(mx[j - 1][i], mx[j - 1][i + (1 << j - 1)]),
		mn[j][i] = min(mn[j - 1][i], mn[j - 1][i + (1 << j - 1)]);
	top = 0; stk[top] = 0;
	rep(i, 1, n) {
		while(top && a[i] > a[stk[top]]) r1[stk[top]] = i - 1, top--;
		l1[i] = stk[top] + 1; stk[++top] = i; r1[i] = n;
	}
	top = 0; stk[top] = 0;
	rep(i, 1, n) {
		while(top && a[i] < a[stk[top]]) r2[stk[top]] = i - 1, top--;
		l2[i] = stk[top] + 1; stk[++top] = i; r2[i] = n;
	}
	/*
	rep(i, 0, n + 1) fa[i] = i, id[i] = i;
	rep(i, 0, n + 1) tvis[i] = false;
	sort(id + 1, id + n + 1, [&](int x, int y) { return a[x] < a[y]; });
	rep(i, 1, n) {
		int x = id[i]; tvis[x] = true;
		int l = gf(x - 1), r = gf(x + 1);
		//cerr << x << " " << l << " " << tvis[l] << " " << r << " " <<  tvis[r] << endl;
		if(tvis[l]) G[x].eb(l), fa[l] = x;
		if(tvis[r]) G[x].eb(r), fa[r] = x;
	} int rta = gf(1);
	//rep(x, 1, n) for(auto y : G[x]) cerr << x << "->"<<y << endl;
	reverse(id + 1, id + n + 1);
	rep(i, 0, n + 1) tvis[i] = false, fa[i] = i;
	rep(i, 1, n) {
		int x = id[i]; tvis[x] = true;
		int l = gf(x - 1), r = gf(x + 1);
		if(tvis[l]) T[x].eb(l), fa[l] = x;
		if(tvis[r]) T[x].eb(r), fa[r] = x;
	} int rtb = gf(1);
	*/
	dis[1] = 0;
	rep(i, 2, n) {
		dis[i] = n + 100; 
		/*
		per(j, i - 1, 1) {
			chkmax(mx, a[j]), chkmin(mn, a[j]);
			if(mx == a[j] && mn == a[i]) lp = j; //chkmin(dis[i], dis[j] + 1);
			if(mx == a[i] && mn == a[j]) lp = j; //chkmin(dis[i], dis[j] + 1);
		} chkmin(dis[i], dis[lp] + 1);
		*/
		//cerr << l1[i] << " " << l2[i] << endl;
		if(l1[i] <= i - 1) {
			int p = getmn(l1[i], i - 1).se;
			//cerr << "get: " << p << endl;
			chkmin(dis[i], dis[p] + 1);
		}
		if(l2[i] <= i - 1) {
			int p = getmx(l2[i], i - 1).se;
			chkmin(dis[i], dis[p] + 1);
		} //cerr << dis[i] << endl;
	} printf("%d\n", dis[n]);
}

void clr() {
	/*
	rep(i, 1, tot) dis[i] = 0, F[i].clear();
	rep(i, 1, n) a[i] = id[i] = ind[i] = dfn[i] = R[i] = 0, G[i].clear(), T[i].clear(), tvis[i] = 0;
	rep(i, 1, n << 2) val[i] = 0;
	tot = 0, tim = 0;
	*/
}

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	for(int T = in; T; T--) solve(), clr(); return 0;
}
