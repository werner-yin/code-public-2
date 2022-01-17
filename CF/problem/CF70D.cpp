#include <bits/stdc++.h>

#define in read<int>()

using namespace std;

using ll = long long;

template < typename T > T read() {
	T x = 0; bool f = 0; char ch = getchar();
	while(!isdigit(ch)) f |= ch == '-', ch = getchar();
	while(isdigit(ch)) x = x * 10 + (ch ^ 48), ch = getchar();
	return f ? -x : x;
}

const int N = 1e5 + 10;
const int inf = 1e9;

struct vect {
	int x, y;
	vect (int _x = 0, int _y = 0) : x(_x), y(_y) { }
	bool friend operator < (vect a, vect b) { return a.x ^ b.x ? a.x < b.x : a.y < b.y; }
	vect friend operator - (vect a, vect b) { return vect(a.x - b.x, a.y - b.y); }
	ll friend operator ^ (vect a, vect b) { return 1ll * a.x * b.y - 1ll * a.y * b.x; }
};
	
template < int N, bool op > struct convex_hull { // op = 0 : 上凸壳, op = 1 : 下凸壳
	set < vect > al;
	bool valid(vect a, vect b, vect c) { // in the convex hull
		ll res = (a - b) ^ (c - b);
		return (res == 0) || ((res < 0) ^ op);
	}
	bool check(vect x) { // in the convex hull
		auto it = al.lower_bound(vect(x.x, -inf)); if(it == al.end()) return false;
		if((*it).x == x.x) return (*it).y == x.y || (((*it).y > x.y) ^ op);
		if(it != al.begin()) return valid(*prev(it), x, *it); return false;
	}
	bool remove(set < vect > :: iterator it) {
		if(it == al.begin() || next(it) == al.end()) return false;
		if(valid(*prev(it), *it, *next(it))) return al.erase(it), true;
		return false;
	}
	void insert(vect x) {
		if(check(x)) return; auto it = al.lower_bound(vect(x.x, -inf)); if(it != al.end() && (*it).x == x.x) al.erase(it);
		al.insert(x); it = al.find(x);
		if(it != al.begin()) { it--; while(remove(it++)) it--; }
		if(++it != al.end()) { while(remove(it--)) it++; }
	}
};

convex_hull < N, 0 > up;
convex_hull < N, 1 > down;

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	int Q = in;
	while(Q--) {
		int op = in, x = in, y = in; vect t(x, y);
		if(op == 1) up.insert(t), down.insert(t);
		else puts(up.check(t) && down.check(t) ? "YES" : "NO");
	}
	return 0;
}
