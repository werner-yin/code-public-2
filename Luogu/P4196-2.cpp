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

struct ve {
	db x, y;
	ve(db _x = 0, db _y = 0) : x(_x), y(_y) {}
	friend ve operator + (ve a, ve b) { return ve(a.x + b.x, a.y + b.y); }
	friend ve operator - (ve a, ve b) { return ve(a.x - b.x, a.y - b.y); }
	friend ve operator * (ve a, db x) { return ve(a.x * x, a.y * x); }
	friend db operator ^ (ve a, ve b) { return a.x * b.y - a.y * b.x; }
	db len() { return sqrt(x * x + y * y); }
} a[N], b[N], c[N];
int n, m, tot, tt;

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

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in - 1; tot = m = in; 
	rep(i, 1, m) a[i].x = in, a[i].y = in;
	while(n--) {
		m = in; rep(i, 1, m) b[i].x = in, b[i].y = in;
		b[m + 1] = b[1]; rep(i, 1, m) cut(b[i], b[i + 1]);
	} a[tot + 1] = a[1]; db ans = 0; rep(i, 1, tot) ans += a[i] ^ a[i + 1];
	printf("%.3lf\n", ans / 2); return 0;
}
