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
	ll x, y;
	ve(ll _x = 0, ll _y = 0) : x(_x), y(_y) {}
	friend ve operator + (ve a, ve b) { return ve(a.x + b.x, a.y + b.y); }
	friend ve operator - (ve a, ve b) { return ve(a.x - b.x, a.y - b.y); }
	friend ve operator * (ve a, db x) { return ve(a.x * x, a.y * x); }
	friend ll operator ^ (ve a, ve b) { return a.x * b.y - a.y * b.x; }
} a[N], b[N];

int n, m, Q;
ll mx[N];

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in; rep(i, 1, n) a[i].x = in, a[i].y = in;
	m = in; rep(i, 1, m) b[i].x = in, b[i].y = in;
	a[n + 1] = a[1]; rep(i, 1, n) mx[i] = -1e18;
	rep(i, 1, n) 
		rep(j, 1, m) chkmax(mx[i], (a[i + 1] - a[i]) ^ (a[i] + b[j]));
	Q = in;
	while(Q--) {
		ve t; t.x = in, t.y = in; bool fl = true;
		rep(i, 1, n) fl &= ((a[i + 1] - a[i]) ^ t) >= mx[i];
		puts(fl ? "Yes" : "No");
	}
}
