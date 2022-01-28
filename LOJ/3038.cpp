#include <bits/stdc++.h>

#define in read<int>()
#define rep(i, x, y) for(int i = (x); i <= (y); i++)

using namespace std;

using ll = long long;

template < typename T > T read() {
	T x = 0; bool f = 0; char ch = getchar();
	while(!isdigit(ch)) f |= ch == '-', ch = getchar();
	while(isdigit(ch)) x = x * 10 + (ch ^ 48), ch = getchar();
	return f ? -x : x;
}

const int N = 3e5 + 10;

int n, Q, l[N], r[N], T[N], A[N], B[N], C[N], D[N];
ll ans[N];

struct node {
	int op, a, b; ll c;
	node(int _op = 0, int _a = 0, int _b = 0, ll _c = 0) : op(_op), a(_a), b(_b), c(_c) { }
} val[N << 2], pv[N];

node operator + (node x, node y) {
	if(x.op) {
		if(y.op) return node(1, x.a, y.b, x.c + y.c + max(0, x.b - y.a));
		else return node(1, x.a, max(min(x.b, y.b), y.a), x.c + max(0, x.b - y.b));
	} else {
		if(y.op) return node(1, min(max(x.a, y.a), x.b), y.b, y.c + max(0, x.a - y.a));
		else if(x.a > y.b) return node(1, x.a, y.b, x.a - y.b);
		else if(x.b < y.a) return node(1, x.b, y.a, 0);
		else return node(0, max(x.a, y.a), min(x.b, y.b), 0);
	}
}

void build(int o = 1, int l = 1, int r = n - 1) {
	if(l == r) return val[o] = pv[l], void(); int mid = l + r >> 1;
	build(o << 1, l, mid); build(o << 1 | 1, mid + 1, r); val[o] = val[o << 1] + val[o << 1 | 1];
}
void upd(const int &pos, const node &v, int o = 1, int l = 1, int r = n - 1) {
	if(l == r) return val[o] = v, void(); int mid = l + r >> 1;
	if(pos <= mid) upd(pos, v, o << 1, l, mid); else upd(pos, v, o << 1 | 1, mid + 1, r);
	val[o] = val[o << 1] + val[o << 1 | 1];
}
node query(const int &xl, const int &xr, int o = 1, int l = 1, int r = n - 1) {
	if(xl == l && r == xr) return val[o]; int mid = l + r >> 1;
	if(xr <= mid) return query(xl, xr, o << 1, l, mid); else if(xl > mid) return query(xl, xr, o << 1 | 1, mid + 1, r);
	else return query(xl, mid, o << 1, l, mid) + query(mid + 1, xr, o << 1 | 1, mid + 1, r);
}

void solve() {
	rep(i, 1, n - 1) pv[i] = node(0, l[i] - i, r[i] - i - 1, 0); build();
	rep(i, 1, Q) {
		if(T[i] == 1) upd(A[i], node(0, B[i] - A[i], C[i] - A[i] - 1, 0));
		else {
			if(A[i] == C[i]) ans[i] = max(B[i] - D[i], 0);
			else if(A[i] < C[i])
				ans[i] = (node(0, B[i] - A[i], B[i] - A[i], 0) + query(A[i], C[i] - 1) + node(0, D[i] - C[i], D[i] - C[i], 0)).c;
		}
	}
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in, Q = in; rep(i, 1, n - 1) l[i] = in, r[i] = in;
	rep(i, 1, Q) T[i] = in, A[i] = in, B[i] = in, C[i] = in, (T[i] == 2) && (D[i] = in);
	if(n == 1) { rep(i, 1, Q) if(T[i] == 2) printf("%d\n", max(B[i] - D[i], 0)); return 0; }
	solve(); reverse(l + 1, l + n); reverse(r + 1, r + n);
	rep(i, 1, Q) A[i] = n - A[i] + (T[i] == 2), (T[i] == 2) && (C[i] = n - C[i] + 1);
	solve(); rep(i, 1, Q) if(T[i] == 2) printf("%lld\n", ans[i]);
	return 0;
}
