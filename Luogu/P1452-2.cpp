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

const int N = 1e5 + 10;

struct vect {
	int x, y;
	vect(int _x = 0, int _y = 0) : x(_x), y(_y) { }
	ll val() { return 1ll * x * x + 1ll * y * y; }
} p[N], stk[N], res[N];

bool operator < (vect a, vect b) { return a.x ^ b.x ? a.x < b.x : a.y < b.y; }
vect operator - (vect a, vect b) { return vect(a.x - b.x, a.y - b.y); }
ll operator ^ (vect a, vect b) { return 1ll * a.x * b.y - 1ll * a.y * b.x; }

int n, top, tot;

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in;
	rep(i, 1, n) p[i].x = in, p[i].y = in;
	sort(p + 1, p + n + 1);
	rep(i, 1, n) {
		while(top > 1 && ((stk[top] - stk[top - 1]) ^ (p[i] - stk[top])) >= 0) top--;
		stk[++top] = p[i];
	}
	rep(i, 1, top) res[++tot] = stk[i];
	top = 0;
	rep(i, 1, n) {
		while(top > 1 && ((stk[top] - stk[top - 1]) ^ (p[i] - stk[top])) <= 0) top--;
		stk[++top] = p[i];
	}
	per(i, top - 1, 2) res[++tot] = stk[i];
	if(tot == 2) return printf("%lld\n", (res[1] - res[2]).val());
	int pos = 1; ll ans = (res[1] - res[2]).val();
	rep(i, 1, tot) {
		int nxt = i % tot + 1;
		while(((res[i] - res[nxt]) ^ (res[pos] - res[i])) <= ((res[i] - res[nxt]) ^ (res[pos % tot + 1] - res[i]))) pos = pos % tot + 1;
		chkmax(ans, (res[pos] - res[i]).val()); chkmax(ans, (res[pos] - res[nxt]).val());
	}
	printf("%lld\n", ans);
	return 0;
}
