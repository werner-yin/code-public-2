#include <bits/stdc++.h>

#define eb emplace_back
#define fi first
#define se second
#define in read<int>()
#define rep(i, x, y) for(int i = (x); i <= (y); i++)
#define per(i, x, y) for(int i = (x); i >= (y); i--)

using namespace std;

using ll = long long;
using pii = pair < ll, ll >;
using vec = vector < int >;

template < typename T > T read() {
	T x = 0; bool f = 0; char ch = getchar();
	while(!isdigit(ch)) f |= ch == '-', ch = getchar();
	while(isdigit(ch)) x = x * 10 + (ch ^ 48), ch = getchar();
	return f ? -x : x;
}

template < typename T > void chkmax(T &x, const T &y) { x = x > y ? x : y; }

const int N = 5610;
const int M = 3e6 + 10;

int n, Q, c[N], xtot, ytot, er[N][N], eu[N][N];
ll bx[N], by[N], x[M], y[M];
ll dp[N][N], ans[M];
pii st[N], ed[N];
vec pot[2][N];

struct line {
	int k; ll b;
} stk[N];
int top;

void ins(ll k, ll b) {
	k = -k;
	while(top && stk[top].k >= k) top--;
	while(top > 1 && (__int128)(stk[top].b - b) * (stk[top - 1].k - k)
		  >= (__int128)(stk[top - 1].b - b) * (stk[top].k - k)) top--;
	stk[++top] = (line){ k, b };
}

ll query(ll x) {
	int l = 1, r = top - 1, ans = top;
	while(l <= r) {
		int mid = l + r >> 1;
		if((stk[mid + 1].b - stk[mid].b) <= (__int128) x * (stk[mid + 1].k - stk[mid].k)) ans = mid, r = mid - 1;
		else l = mid + 1;
	}// cerr << l << " " << r << " " << ans << " " << top << endl;
	return -stk[ans].k * x + stk[ans].b;
}

signed main() {
#ifndef ONLINE_JUDGE
	freopen("guard.in", "r", stdin);// freopen("guard.out", "w", stdout);
#endif
	n = in, Q = in;
	rep(i, 1, n) {
		int t = in, a = in, b = in; c[i] = in / 2;
		ll x = t, y = a; st[i] = { x + y, x - y };
		x = t + abs(a - b), y = b; ed[i] = { x + y, x - y };
		bx[++xtot] = st[i].fi, bx[++xtot] = ed[i].fi;
		by[++ytot] = st[i].se, by[++ytot] = ed[i].se;
	} sort(bx + 1, bx + xtot + 1); sort(by + 1, by + ytot + 1);
	xtot = unique(bx + 1, bx + xtot + 1) - bx - 1; ytot = unique(by + 1, by + ytot + 1) - by - 1;
	auto getpos = [](pii v) { return pii(lower_bound(bx + 1, bx + xtot + 1, v.fi) - bx, lower_bound(by + 1, by + ytot + 1, v.se) - by); };
	rep(i, 1, n) 
		st[i] = getpos(st[i]), ed[i] = getpos(ed[i]);
	rep(i, 1, n)
		if(st[i].fi == ed[i].fi)
			rep(j, min(st[i].se, ed[i].se), max(st[i].se, ed[i].se) - 1) chkmax(eu[st[i].fi][j], c[i]);
		else rep(j, min(st[i].fi, ed[i].fi), max(st[i].fi, ed[i].fi) - 1) chkmax(er[j][st[i].se], c[i]);
	per(i, xtot, 1) per(j, ytot, 1)
		dp[i][j] =
		max(dp[i + 1][j] + 1ll * er[i][j] * (bx[i + 1] - bx[i]), dp[i][j + 1] + 1ll * eu[i][j] * (by[j + 1] - by[j]));
	rep(i, 1, Q) {
		x[i] = in, y[i] = in; tie(x[i], y[i]) = pii{ x[i] + y[i], x[i] - y[i] };
		pot[0][lower_bound(bx + 1, bx + xtot + 1, x[i]) - bx].eb(i);
		pot[1][lower_bound(by + 1, by + ytot + 1, y[i]) - by].eb(i);
	} bx[0] = by[0] = -1e18;
	rep(i, 1, xtot) {
		top = 0; sort(pot[0][i].begin(), pot[0][i].end(), [](int a, int b) { return y[a] < y[b]; });
		while(pot[0][i].size() && y[pot[0][i].back()] > by[ytot]) pot[0][i].pop_back();
		per(j, ytot, 1) {
			ins(er[i - 1][j], dp[i][j]);
			while(pot[0][i].size() && y[pot[0][i].back()] > by[j - 1])
				chkmax(ans[pot[0][i].back()], query(bx[i] - x[pot[0][i].back()])), pot[0][i].pop_back(); 
		} 
	}
	rep(j, 1, ytot) {
		top = 0; sort(pot[1][j].begin(), pot[1][j].end(), [](int a, int b) { return x[a] < x[b]; });
		while(pot[1][j].size() && x[pot[1][j].back()] > bx[xtot]) pot[1][j].pop_back();
		per(i, xtot, 1) {
			ins(eu[i][j - 1], dp[i][j]);
			while(pot[1][j].size() && x[pot[1][j].back()] > bx[i - 1])
				chkmax(ans[pot[1][j].back()], query(by[j] - y[pot[1][j].back()])), pot[1][j].pop_back();
		} 
	} rep(i, 1, Q) printf("%lld\n", ans[i]); return 0;
}
