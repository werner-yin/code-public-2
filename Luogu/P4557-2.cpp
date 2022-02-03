#include <bits/stdc++.h>

#define in read<int>()
#define lin read<ll>()
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

const int N = 2e5 + 10;

int n, m, q;
struct node {
	int x, y;
	node(int _x = 0, int _y = 0) : x(_x), y(_y) { }
	friend node operator + (node a, node b) { return node(a.x + b.x, a.y + b.y); }
	friend node operator - (node a, node b) { return node(a.x - b.x, a.y - b.y); }
	friend ll operator * (node a, node b) { return 1ll * a.x * b.x + 1ll * a.y * b.y; }
	friend ll operator ^ (node a, node b) { return 1ll * a.x * b.y - 1ll * a.y * b.x; }
	db dis() { return sqrtl(1ll * x * x + 1ll * y * y); }
} a[N], b[N], stk[N], res[N], u[N], v[N], w[N], base;
int top, tot;

void convex_hull(node *a, int &n) {
	rep(i, 2, n) 
		if(a[i].y < a[1].y || (a[i].y == a[1].y && a[i].x < a[1].x)) swap(a[i], a[1]);
	sort(a + 2, a + n + 1, [&](auto x, auto y) {
							   ll t = (x - a[1]) ^ (y - a[1]);
							   if(t == 0) return (x - a[1]).dis() < (y - a[1]).dis();
							   else return t > 0;
						   });
	stk[top = 1] = a[1];
	rep(i, 2, n) {
		while(top > 1 && ((stk[top] - stk[top - 1]) ^ (a[i] - stk[top - 1])) <= 0) top--;
		stk[++top] = a[i];
	} n = top; rep(i, 1, top) a[i] = stk[i];
}

void minkowski() {
	rep(i, 1, n) u[i] = a[i % n + 1] - a[i];
	rep(i, 1, m) v[i] = b[i % m + 1] - b[i];
	stk[top = 1] = a[1] + b[1]; int i = 1, j = 1;
	while(i <= n && j <= m) {
		ll t = u[i] ^ v[j];
		if(t >= 0) top++, stk[top] = stk[top - 1] + u[i++];
		else top++, stk[top] = stk[top - 1] + v[j++];
	} while(i <= n) top++, stk[top] = stk[top - 1] + u[i++];
	while(j <= m) top++, stk[top] = stk[top - 1] + v[j++];
	tot = top; rep(i, 1, top) res[i] = stk[i];
}

bool check(node x) {
	if((x ^ res[2]) > 0 || ((x ^ res[2]) == 0 && x.dis() > res[2].dis())) return false;
	if((res[tot] ^ x) > 0 || ((res[tot] ^ x) == 0 && x.dis() > res[tot].dis())) return false;
	int p = lower_bound(res + 1, res + tot + 1, x, [&](auto a, auto b) {
													ll t = a ^ b;
													if(t == 0) return a.dis() < b.dis();
													else return t > 0;
												}) - res - 1;
	return ((res[p + 1] - res[p]) ^ (x - res[p])) >= 0;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in, m = in, q = in;
	rep(i, 1, n) a[i].x = in, a[i].y = in;
	rep(i, 1, m) b[i].x = -in, b[i].y = -in;
	convex_hull(a, n); convex_hull(b, m); minkowski(); convex_hull(res, tot); 
	base = res[1]; rep(i, 1, tot) res[i] = res[i] - base;
	while(q--) { node t; t.x = in, t.y = in; t = t - base; printf("%d\n", check(t)); }
	return 0;
}
