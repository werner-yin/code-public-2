#include <bits/stdc++.h>

#define in read<int>()
#define rep(i, x, y) for(int i = (x); i <= (y); i++)
#define per(i, x, y) for(int i = (x); i >= (y); i--)

using namespace std;

using ll = long long;
using db = double;

template < typename T > T read() {
	T x = 0; bool f = 0; char ch = getchar();
	while(!isdigit(ch)) f |= ch == '-', ch = getchar();
	while(isdigit(ch)) x = x * 10 + (ch ^ 48), ch = getchar();
	return f ? -x : x;
}

const int N = 1e5 + 10;
const int inf = 1e9;

int deltim[N], n, m;

struct vect {
	int x, y;
	vect (int _x = 0, int _y = 0) : x(_x), y(_y) { }
	bool friend operator < (vect a, vect b) { return a.x ^ b.x ? a.x < b.x : a.y < b.y; }
	vect friend operator - (vect a, vect b) { return vect(a.x - b.x, a.y - b.y); }
	ll friend operator ^ (vect a, vect b) { return 1ll * a.x * b.y - 1ll * a.y * b.x; }
	db val() { return sqrtl(1ll * x * x + 1ll * y * y); }
};
	
template < int N, bool op > struct convex_hull {
	set < vect > al; db res;
	convex_hull() { al.clear(); res = 0; }
	bool valid(vect a, vect b, vect c) {
		ll res = (a - b) ^ (c - b);
		return (res == 0) || ((res < 0) ^ op);
	}
	bool check(vect x) {
		auto it = al.lower_bound(vect(x.x, -inf)); if(it == al.end()) return false;
		if((*it).x == x.x) return (*it).y == x.y || (((*it).y > x.y) ^ op);
		if(it != al.begin()) return valid(*prev(it), x, *it); return false;
	}
	db calc(set < vect > :: iterator it) {
		if(it == al.begin() || it == al.end()) return 0; auto itt = prev(it);
		return (*it - *itt).val(); 
	}
	bool remove(set < vect > :: iterator it) {
		if(it == al.begin() || next(it) == al.end()) return false;
		if(valid(*prev(it), *it, *next(it)))
			return res -= calc(it), res -= calc(next(it)), al.erase(it++), res += calc(it), true;
		return false;
	}
	void insert(vect x) {
		if(check(x)) return; auto it = al.lower_bound(vect(x.x, -inf));
		if(it != al.end() && (*it).x == x.x) res -= calc(it), res -= calc(next(it)), al.erase(it++);
		else res -= calc(it);
		al.insert(x); it = al.find(x); res += calc(it); res += calc(next(it));
		if(it != al.begin()) { it--; while(remove(it++)) it--; }
		if(++it != al.end()) { while(remove(it--)) it++; }
	}
};

convex_hull < N, 0 > up;

int x[N], y[N], Q, op[N], v[N];
db ans[N];

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in; int x = in, y = in; m = in;
	up.insert(vect(x, y)); up.insert(vect(0, 0)); up.insert(vect(n, 0));
	rep(i, 1, m) ::x[i] = in, ::y[i] = in;
	Q = in; 
	rep(i, 1, Q) op[i] = in, (op[i] == 1) && (deltim[v[i] = in] = i);
	rep(i, 1, m) if(!deltim[i]) up.insert(vect(::x[i], ::y[i]));
	per(i, Q, 1) {
		if(op[i] == 1) up.insert(vect(::x[v[i]], ::y[v[i]]));
		else ans[i] = up.res;
	}
	rep(i, 1, Q) if(op[i] == 2) printf("%.2lf\n", ans[i]);
	return 0;
}
