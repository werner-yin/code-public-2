#include <bits/stdc++.h>
#include "meeting.h"

#define eb emplace_back
#define rep(i, x, y) for(int i = (x); i <= (y); i++)

using namespace std;

using pii = pair < int, int >;
using veg = vector < pii >;
using vec = vector < int >;

const int N = 1010;

vec t[N];
int tot, n;
veg edge;

vec operator + (vec a, vec b) { for(auto v : b) a.eb(v); return a; }

void check(const vec &a, const vec &b) {
	if(!a.size() || !b.size()) return;
	if(a.size() == 1 && b.size() == 1) {
		if(!meeting(a + b)) edge.eb(a[0], b[0]);
		return;
	}
	vec a1, a2 = a; while(a1.size() < a2.size()) a1.eb(a2.back()), a2.pop_back();
	vec b1, b2 = b; while(b1.size() < b2.size()) b1.eb(b2.back()), b2.pop_back();
	for(const auto &v1 : { a1, a2 })
		for(const auto &v2 : { b1, b2 }) {
			if(!meeting(v1 + v2)) check(v1, v2);
		}
}

veg solve(int tn) {
	n = tn;
	rep(i, 0, n - 1) {
		bool fl = 0;
		rep(j, 1, tot) {
			t[j].eb(i); if(meeting(t[j])) { fl = true; break; } t[j].pop_back();
		} if(!fl) ++tot, t[tot].eb(i);
	}
	rep(i, 1, tot) rep(j, i + 1, tot) check(t[i], t[j]);
	return edge;
}
