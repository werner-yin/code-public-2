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
constexpr db eps = 1e-9;

db comp(db a, db b) { return fabs(a - b) < eps ? 0 : a < b ? - 1 : 1; }

int n;

struct ve {
	db x, y;
	ve(db x = 0, db y = 0) : x(x), y(y) { }
	friend ve operator + (ve a, ve b) { return ve(a.x + b.x, a.y + b.y); }
	friend ve operator - (ve a, ve b) { return ve(a.x - b.x, a.y - b.y); }
	friend ve operator * (ve a, db b) { return ve(a.x * b, a.y * b); }
	friend db operator * (ve a, ve b) { return a.x * b.y - a.y * b.x; } // notice: cross
	friend db operator ^ (ve a, ve b) { return a.x * b.x + a.y * b.y; } // notice: dot
	ve rt90() { return ve(y, -x); }
	db len() { return hypot(x, y); }
	db len2() { return x * x + y * y; }
} a[N];

ve get_cross(ve a, ve b, ve c, ve d) {
	db k = ((d - a) * (c - a)) / ((d - a) * (c - a) + (d - c) * (b - c));
	return (b - a) * k + a;
}

ve get_circle(ve a, ve b, ve c) {
	return get_cross((a + b) * 0.5, (a + b) * 0.5 + (b - a).rt90(), (b + c) * 0.5, (b + c) * 0.5 + (b - c).rt90());
}

using circle = pair < ve, db >;

mt19937 rnd(random_device{}());

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in; rep(i, 1, n) scanf("%lf %lf", &a[i].x, &a[i].y);
	shuffle(a + 1, a + n + 1, rnd);
	circle C = { a[1], 0 };
	rep(i, 2, n) {
		if(comp((C.fi - a[i]).len2(), C.se) != 1) continue;
		C = { a[i], 0 };
		rep(j, 1, i - 1) {
			if(comp((C.fi - a[j]).len2(), C.se) != 1) continue;
			C = { (a[i] + a[j]) * 0.5, (a[i] - a[j]).len2() * 0.25 };
			rep(k, 1, j - 1) {
				if(comp((C.fi - a[k]).len2(), C.se) != 1) continue;
				C.fi = get_circle(a[i], a[j], a[k]);
				C.se = max({ (a[i] - C.fi).len2(), (a[j] - C.fi).len2(), (a[k] - C.fi).len2() });
			}
		}
	} printf("%.10lf\n%.10lf %.10lf\n", sqrt(C.se), C.fi.x, C.fi.y);
	return 0;
}
