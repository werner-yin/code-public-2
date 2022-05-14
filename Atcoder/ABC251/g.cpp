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
const db eps = 1e-9;

struct ve {
	db x, y; int id;
	ve(db _x = 0, db _y = 0, int id = 0) : x(_x), y(_y), id(id) {}
	friend ve operator + (ve a, ve b) { return ve(a.x + b.x, a.y + b.y, a.id); }
	friend ve operator - (ve a, ve b) { return ve(a.x - b.x, a.y - b.y, a.id); }
	friend ve operator * (ve a, db x) { return ve(a.x * x, a.y * x); }
	friend db operator ^ (ve a, ve b) { return a.x * b.y - a.y * b.x; }
	db len() { return sqrt(x * x + y * y); }
	friend bool operator < (ve a, ve b) {
		db res = a ^ b;
		if(fabs(res) < eps) return a.len() > b.len();
		return res > 0;
	}
} a[N], b[N], c[N], d[N], stk[N];
int n, m, tot, tt, q, top;

ve get(ve a1, ve a2, ve b1, ve b2) {
	ve c = b1 - a1; db A = (b2 - b1) ^ c, B = (b2 - b1) ^ (a2 - a1);
	return a1 + ((a2 - a1) * (A / B));
}

void cut(ve A, ve B) {
	a[tot + 1] = a[1]; int tt = 0;
	rep(i, 1, tot)
		if(((A - a[i]) ^ (B - a[i])) >= 0) {
			c[++tt] = a[i];
			if(((A - a[i + 1]) ^ (B - a[i + 1])) < 0)
				c[++tt] = get(a[i], a[i + 1], A, B);
		} else if(((A - a[i + 1]) ^ (B - a[i + 1])) >= 0)
			c[++tt] = get(a[i], a[i + 1], A, B);
	rep(i, 1, tt) a[i] = c[i]; tot = tt;
}

bool vis[N];

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in; tot = n; 
	rep(i, 1, tot) a[i].x = d[i].x = in, a[i].y = d[i].y = in;
	//rep(i, 1, tot) cerr << a[i].x << " " << a[i].y << endl;
	m = in - 1;
	int tu = in, tv = in;
	rep(i, 1, tot) a[i].x += tu, a[i].y += tv;
	while(m--) {
		int u = in, v = in;
		rep(i, 1, n) b[i].x = d[i].x + u, b[i].y = d[i].y + v;
		b[n + 1] = b[1]; rep(i, 1, n) cut(b[i], b[i + 1]);
	} 
	//rep(i, 1, tot) cerr << a[i].x << " " << a[i].y << endl;
	//sort(a + 1, a + tot + 1);
	//rep(i, 1, tot) cerr << a[i].x << " " << a[i].y << endl;
	q = in;
	rep(i, 1, q) {
		int x = in, y = in;
		a[++tot] = ve(x, y); a[tot].id = i;
	} n = tot;
	rep(i, 2, n) if(a[i].x < a[1].x) swap(a[i], a[1]); 
	rep(i, 2, n) a[i] = a[i] - a[1]; a[1] = ve(0, 0, a[1].id);
	sort(a + 2, a + n + 1, [](auto a, auto b) { db res = a ^ b; if(fabs(res) < eps) return a.len() > b.len(); return res < 0; });
	tot = 0; 
	rep(i, 2, n) {
		while(tot > 1 && ((a[i] - stk[tot - 1]) ^ (stk[tot] - stk[tot - 1])) <= 0) tot--;
		stk[++tot] = a[i];
	} a[0] = a[1]; rep(i, 1, tot) a[i] = stk[i];
	rep(i, 0, tot) vis[a[i].id] = true;
	rep(i, 1, q) if(!vis[i]) puts("Yes"); else puts("No");
}
